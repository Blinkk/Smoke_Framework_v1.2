/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "UIComponent.h"
#include "Engine.h"

namespace Smoke
{
	UIComponent::UIComponent()
	{
		// Default values
		_renderer = nullptr;

		componentType = COMPONENTS::UI_COMPONENT;
	}


	UIComponent::~UIComponent()
	{
		// Ensure memory is released
		if (_renderer)
			Shutdown();
	}


	void UIComponent::Render()
	{
		if (_renderer->HasTexture())
		{
			_renderer->Render();
		}
	}


	void UIComponent::HandleEvent(IEvent* e)
	{
		/*
			Handle registered events
		*/
	}


	bool UIComponent::Initialize(float scaleX, float scaleY, unsigned int frameWidth,
		unsigned int frameHeight, unsigned int numCol, unsigned int startFrame, 
		unsigned int endFrame, unsigned int delay, int animDirection, unsigned int uiComponentType,
		float rotationInRadians, float newX, float newY, bool active, std::string textureToUse,
		std::string text, D3DCOLOR textColor)
	{
		_uiComponentType = uiComponentType;

		_fontObject = Font();
		_width = frameWidth;
		_height = frameHeight;
		_active = active;
		_text = text;
		_textColor = textColor;

		////////////////////////
		// Initialize Renderer
		////////////////////////
		_renderer = new TwoDRenderer();
		if (!_renderer)
		{
			debug << "Failed to create TwoDRenderer in UIComponent" << std::endl;
			return false;
		}
		else
		{
			_renderer->Initialize(scaleX, scaleY, frameWidth, frameHeight,
				numCol, startFrame, endFrame, delay, animDirection, rotationInRadians,
				newX, newY, textureToUse);
		}

		/////////////////////////
		// Register Events
		/////////////////////////
		switch (_uiComponentType)
		{
		case UI_COMPONENTS::UI_BUTTON:
			g_Engine->GetEventManager()->RegisterListener(this, Events::CLICK_DOWN);
			g_Engine->GetEventManager()->RegisterListener(this, Events::CLICK_UP);
			break;

		default:
			break;
		}

		return true;
	}


	void UIComponent::Update(float deltaTime)
	{
		_renderer->Update();
	}


	void UIComponent::Shutdown()
	{
		if (_renderer)
		{
			delete _renderer;
			_renderer = nullptr;
		}

		/////////////////////////
		// Purge Event Listeners
		/////////////////////////
		switch (_uiComponentType)
		{
		case UI_COMPONENTS::UI_BUTTON:
			g_Engine->GetEventManager()->PurgeListener(this->componentID, Events::CLICK_DOWN);
			g_Engine->GetEventManager()->PurgeListener(this->componentID, Events::CLICK_UP);
			break;

		default:
			break;
		}
	}


	//////////////////////////
	// Utility Functions
	//////////////////////////
}