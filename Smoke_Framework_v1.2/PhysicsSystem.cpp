/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "Engine.h"

namespace Smoke
{
	PhysicsSystem::PhysicsSystem()
	{
		systemType = PHYSICS_SYSTEM;
	}


	PhysicsSystem::~PhysicsSystem()
	{
		// Ensure memory is released
		if (!_physicsComponents.empty())
			Shutdown();
	}


	bool PhysicsSystem::Initialize()
	{
		debug << "\tPhysics System initialized" << std::endl;
		return true;
	}


	void PhysicsSystem::Update(float deltaTime)
	{
		// Call update for each graphics component
		if (!_physicsComponents.empty())
		{
			for (_compIt = _physicsComponents.begin(); _compIt != _physicsComponents.end(); ++_compIt)
			{
				(*_compIt)->Update(deltaTime);
			}
		}
	}


	void PhysicsSystem::Shutdown()
	{
		if (!_physicsComponents.empty())
		{
			// Delete each component
			for (_compIt = _physicsComponents.begin(); _compIt != _physicsComponents.end();)
			{
				delete (*_compIt);
				_compIt = _physicsComponents.erase(_compIt);
			}
		}
		if (_physicsComponents.empty())
			debug << "\tPhysicsSystem shutdown" << std::endl;
		else
			debug << "\tError shutting down PhysicsSystem" << std::endl;
	}


	void PhysicsSystem::AddComponent(IComponent* pComponent)
	{
		if (pComponent != nullptr)
		{
			// Cast to GraphicsComponent type
			PhysicsComponent* pTemp = nullptr;
			pTemp = dynamic_cast<PhysicsComponent*>(pComponent);

			if (pTemp)
			{
				_physicsComponents.push_back(pTemp);
			}
			else
			{
				debug << "Failed to add component to PhysicsSytem, cast unsuccessful" << std::endl;
				return;
			}
		}
		else
		{
			debug << "Failed to add component to PhysicsSytem, component is null" << std::endl;
			return;
		}
	}


	void PhysicsSystem::RemoveComponent(unsigned int componentID)
	{
		for (_compIt = _physicsComponents.begin(); _compIt != _physicsComponents.end(); ++_compIt)
		{
			if ((*_compIt)->componentID == componentID)
			{
				delete (*_compIt);
				_compIt = _physicsComponents.erase(_compIt);
			}
		}
	}
}