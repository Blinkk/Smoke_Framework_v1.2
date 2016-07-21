/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "Engine.h"

namespace Smoke
{
	UISystem::UISystem()
	{
		systemType = SYSTEMS::UI_SYSTEM;
	}


	UISystem::~UISystem()
	{

	}


	bool UISystem::Initialize()
	{
		debug << "\tUISystem Systems initialized" << std::endl;
		return true;
	}


	void UISystem::Update(float deltaTime)
	{
		// Call update for each graphics component
		if (!_uiComponents.empty())
		{
			for (_compIt = _uiComponents.begin(); _compIt != _uiComponents.end(); ++_compIt)
			{
				(*_compIt)->Update(deltaTime);
			}
		}
	}


	void UISystem::Render()
	{
		if (!_uiComponents.empty())
		{
			for (_compIt = _uiComponents.begin(); _compIt != _uiComponents.end(); ++_compIt)
			{
				(*_compIt)->Render();
			}
		}
	}


	void UISystem::Shutdown()
	{
		// Release memory used by UI
		if (!_uiComponents.empty())
		{
			for (_compIt = _uiComponents.begin(); _compIt != _uiComponents.end();)
			{
				delete (*_compIt);
				_compIt = _uiComponents.erase(_compIt);
			}
			_uiComponents.clear();
		}
		
		if (_uiComponents.empty())
			debug << "\tUISystem shutdown" << std::endl;
		else
			debug << "\tError shutting down UISystem" << std::endl;
	}


	//////////////////////
	// Utility Functions
	//////////////////////
	void UISystem::AddComponent(IComponent* pComponent)
	{
		if (pComponent)
		{
			// Cast to GraphicsComponent type
			UIComponent* pTemp = nullptr;
			pTemp = dynamic_cast<UIComponent*>(pComponent);

			if (pTemp)
			{
				_uiComponents.push_back(pTemp);
			}
			else
			{
				debug << "Failed to add component to UISystem, cast unsuccessful" << std::endl;
				return;
			}
		}
		else
		{
			debug << "Failed to add UIComponent to UISystem, component is null" << std::endl;
			return;
		}
	}

	
	void UISystem::RemoveComponent(unsigned int componentID)
	{
		for (_compIt = _uiComponents.begin(); _compIt != _uiComponents.end(); ++_compIt)
		{
			if ((*_compIt)->componentID == componentID)
			{
				delete (*_compIt);
				_uiComponents.erase(_compIt);
			}
		}
	}
}