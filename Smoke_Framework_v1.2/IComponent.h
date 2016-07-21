/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef ICOMPONENT_H
#define ICOMPONENT_H
#include "Event.h"

enum COMPONENTS
{
	INPUT_COMPONENT = 0,
	ENTITY_COMPONENT = 1,
	PHYSICS_COMPONENT = 2,
	GRAPHICS_COMPONENT = 3,

	UI_COMPONENT = 10		// Not to be attached to GameObjects
};

namespace Smoke
{
	class IComponent
	{
	public:
		unsigned int componentType;		// Type of component
		unsigned int componentID;		// Unique identifier for each component (used for event system)
	
		IComponent() {};

		// Forces each component to realease its own memory. 
		virtual ~IComponent() {}

		/*
			This function is responsible for handling events that 
			a component is registered for. This enables the
			different components to send messages (events)
			to each other in order to communicate without them
			having to have explicit knowledge of each other.
		*/
		virtual void HandleEvent(IEvent*) = 0;

		/*
			Each component must define their own version of 
			these functions. This defines how each component
			behaves and how it affects the object.

			(Optional) Initialize(...): Register component for events,
			create necessary objects and initialize values

			Update(): Manage update logic for all values/objects
			stored within the component

			Shutdown(): Release any memory allocated within the 
			component and purge event listeners
		*/
		virtual void Update(float deltaTime) = 0;
		virtual void Shutdown() = 0;
	};
}

#endif