/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "EntityComponent.h"

namespace Smoke
{
	EntityComponent::EntityComponent()
	{
		// Default values
		_health = 0;
		_lives = 0;

		componentType = COMPONENTS::ENTITY_COMPONENT;
	}


	EntityComponent::~EntityComponent()
	{
		// No memory to release
	}


	void EntityComponent::HandleEvent(IEvent* e)
	{
		/*
			Handle registered events
		*/
	}


	bool EntityComponent::Initialize(unsigned int health, unsigned int lives)
	{
		/////////////////////////
		// Set health and lives
		/////////////////////////
		_health = health;
		_lives = lives;

		/////////////////////////
		// Register Events
		/////////////////////////


		return true;
	}


	void EntityComponent::Update(float deltaTime)
	{
		// No update logic
	}


	void EntityComponent::Shutdown()
	{
		// No memory to release
	}


	//////////////////////////
	// Utility Functions
	//////////////////////////
}