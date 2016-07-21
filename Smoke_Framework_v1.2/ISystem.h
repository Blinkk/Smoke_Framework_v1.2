/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef ISYSTEM_H
#define ISYSTEM_H
#include "IComponent.h"
#include <vector>

/*
	Each system that inherits from this class must use a 
	static (SYSTEM_NAME)& GetInstance() that calls upon a private
	constructor. This ensures that there can only ever be
	one instance of a given system.
*/

enum SYSTEMS
{
	GRAPHICS_SYSTEM = 0,
	PHYSICS_SYSTEM = 1,
	ENTITY_SYSTEM = 2,
	INPUT_SYSTEM = 3,

	UI_SYSTEM = 10
};

namespace Smoke
{
	class ISystem
	{
	protected:
		ISystem() {}

	public:
		unsigned int systemType;

		// Forces each system to realease its own memory. 
		virtual ~ISystem() {}

		/*
			Initialize(): Create necessary objects and initialize values

			Update(): Manage update logic for all values/objects
			stored within the system

			Shutdown(): Release any memory allocated in system

			AddComponent(): Add a new component to the system

			RemoveComponent(): Remove a component from the system
		*/
		virtual bool Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Shutdown() = 0;
		virtual void AddComponent(IComponent* pComponent) = 0;
		virtual void RemoveComponent(unsigned int componentID) = 0;
	};
}

#endif