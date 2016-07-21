/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "Engine.h"

namespace Smoke
{
	GraphicsSystem::GraphicsSystem()
	{
		systemType = SYSTEMS::GRAPHICS_SYSTEM;
	}


	GraphicsSystem::~GraphicsSystem()
	{
		// Ensure memory is released
		if (!_graphicsComponents.empty())
			Shutdown();
	}


	void GraphicsSystem::Render()
	{
		// Call update for each graphics component
		if (!_graphicsComponents.empty())
		{
			for (_compIt = _graphicsComponents.begin(); _compIt != _graphicsComponents.end(); ++_compIt)
			{
				(*_compIt)->Render();
			}
		}
	}


	bool GraphicsSystem::Initialize()
	{
		debug << "\tGraphics Systems initialized" << std::endl;
		return true;
	}


	void GraphicsSystem::Update(float deltaTime)
	{
		// Call update for each graphics component
		if (!_graphicsComponents.empty())
		{
			for (_compIt = _graphicsComponents.begin(); _compIt != _graphicsComponents.end(); ++_compIt)
			{
				(*_compIt)->Update(deltaTime);
			}
		}
	}


	void GraphicsSystem::Shutdown()
	{
		if (!_graphicsComponents.empty())
		{
			// Delete each component
			for (_compIt = _graphicsComponents.begin(); _compIt != _graphicsComponents.end();)
			{
				delete (*_compIt);
				_compIt = _graphicsComponents.erase(_compIt);
			}
		}
		if (_graphicsComponents.empty())
			debug << "\tGraphicsSystem shutdown" << std::endl;
		else
			debug << "\tError shutting down GraphicsSystem" << std::endl;
	}


	void GraphicsSystem::AddComponent(IComponent* pComponent)
	{
		if (pComponent != nullptr)
		{
			// Cast to GraphicsComponent type
			GraphicsComponent* pTemp = nullptr;
			pTemp = dynamic_cast<GraphicsComponent*>(pComponent);

			if (pTemp)
			{
				_graphicsComponents.push_back(pTemp);
			}
			else
			{
				debug << "Failed to add component to GraphicsSystem, cast unsuccessful" << std::endl;
				return;
			}
		}
		else
		{
			debug << "Failed to add component to GraphicsSystem, component is null" << std::endl;
			return;
		}
	}


	void GraphicsSystem::RemoveComponent(unsigned int componentID)
	{
		for (_compIt = _graphicsComponents.begin(); _compIt != _graphicsComponents.end(); ++_compIt)
		{
			if ((*_compIt)->componentID == componentID)
			{
				delete (*_compIt);
				_compIt = _graphicsComponents.erase(_compIt);
			}
		}
	}
}