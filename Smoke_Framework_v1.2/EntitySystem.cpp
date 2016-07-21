/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "Engine.h"

namespace Smoke
{
	EntitySystem::EntitySystem()
	{
		systemType = ENTITY_SYSTEM;
	}


	EntitySystem::~EntitySystem()
	{
		// Ensure memory is released
		if (!_entityComponents.empty())
			Shutdown();
	}


	bool EntitySystem::Initialize()
	{
		debug << "\tEntity System initialized" << std::endl;
		return true;
	}


	void EntitySystem::Update(float deltaTime)
	{
		// Call update for each graphics component
		if (!_entityComponents.empty())
		{
			for (_compIt = _entityComponents.begin(); _compIt != _entityComponents.end(); ++_compIt)
			{
				(*_compIt)->Update(deltaTime);
			}
		}
	}


	void EntitySystem::Shutdown()
	{
		if (!_entityComponents.empty())
		{
			// Delete each component
			for (_compIt = _entityComponents.begin(); _compIt != _entityComponents.end();)
			{
				delete (*_compIt);
				_compIt = _entityComponents.erase(_compIt);
			}
		}
		if (_entityComponents.empty())
			debug << "\tEntitySystem shutdown" << std::endl;
		else
			debug << "\tError shutting down EntitySystem" << std::endl;
	}


	void EntitySystem::AddComponent(IComponent* pComponent)
	{
		if (pComponent != nullptr)
		{
			// Cast to GraphicsComponent type
			EntityComponent* pTemp = nullptr;
			pTemp = dynamic_cast<EntityComponent*>(pComponent);

			if (pTemp)
			{
				_entityComponents.push_back(pTemp);
			}
			else
			{
				debug << "Failed to add component to EntitySystem, cast unsuccessful" << std::endl;
				return;
			}
		}
		else
		{
			debug << "Failed to add component to EntitySystem, component is null" << std::endl;
			return;
		}
	}


	void EntitySystem::RemoveComponent(unsigned int componentID)
	{
		for (_compIt = _entityComponents.begin(); _compIt != _entityComponents.end(); ++_compIt)
		{
			if ((*_compIt)->componentID == componentID)
			{
				delete (*_compIt);
				_compIt = _entityComponents.erase(_compIt);
			}
		}
	}
}