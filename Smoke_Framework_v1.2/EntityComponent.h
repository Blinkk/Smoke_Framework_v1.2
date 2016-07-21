/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef ENTITY_COMPONENT_H
#define ENTITY_COMPONENT_H
#include "IComponent.h"

namespace Smoke
{
	class EntityComponent : public IComponent
	{
	private:
		unsigned int _health;		// Health of entity
		unsigned int _lives;		// # of lives of entity

		//////////////////////////
		// Utility Functions
		//////////////////////////
		/*
			Internal functions used to streamline code
		*/

	public:
		EntityComponent();
		~EntityComponent();

		void HandleEvent(IEvent* e) override;
		bool Initialize(unsigned int health, unsigned int lives);
		void Update(float deltaTime) override;
		void Shutdown() override;
	};
}

#endif