/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "GraphicsComponent.h"

namespace Smoke
{
	GraphicsComponent::GraphicsComponent()
	{
		// Default values
		_renderer = nullptr;

		componentType = COMPONENTS::GRAPHICS_COMPONENT;
	}


	GraphicsComponent::~GraphicsComponent()
	{
		// Ensure memory is released
		if (_renderer)
			Shutdown();
	}


	void GraphicsComponent::Render()
	{
		if (_renderer->HasTexture())
		{
			_renderer->Render();
		}
	}


	void GraphicsComponent::HandleEvent(IEvent* e)
	{
		/*
			Handle registered events
		*/
	}


	bool GraphicsComponent::Initialize(float scaleX, float scaleY, 
		unsigned int frameWidth, unsigned int frameHeight, 
		unsigned int numCol, unsigned int startFrame, unsigned int endFrame,
		unsigned int delay, int animDirection, float rotationInRadians,
		float newX, float newY,	std::string textureToUse)
	{
		////////////////////////
		// Initialize Renderer
		////////////////////////
		_renderer = new TwoDRenderer();
		if (!_renderer)
		{
			debug << "Failed to create TwoDRenderer in GraphicsComponent" << std::endl;
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


		return true;
	}


	void GraphicsComponent::Update(float deltaTime)
	{
		_renderer->Update();
	}


	void GraphicsComponent::Shutdown()
	{
		if (_renderer)
		{
			delete _renderer;
			_renderer = nullptr;
		}
	}


	//////////////////////////
	// Utility Functions
	//////////////////////////
}