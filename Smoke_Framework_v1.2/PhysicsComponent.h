/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H
#include "IComponent.h"

namespace Smoke
{
	class PhysicsComponent : public IComponent
	{
	private:
		/*
			Stores variables, objects to be managed by physics component
		*/

		//////////////////////////
		// Utility Functions
		//////////////////////////
		/*
			Internal functions used to streamline code
		*/

	public:
		PhysicsComponent();
		~PhysicsComponent();

		void HandleEvent(IEvent* e) override;
		bool Initialize();
		void Update(float deltaTime) override;
		void Shutdown() override;
	};
}

#endif