/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "PhysicsComponent.h"

namespace Smoke
{
	PhysicsComponent::PhysicsComponent()
	{
		/*
			Initialize values to default and pointers to null
		*/
		componentType = COMPONENTS::PHYSICS_COMPONENT;
	}


	PhysicsComponent::~PhysicsComponent()
	{
		/*
			Call shutdown and ensure everything is released
		*/
	}


	void PhysicsComponent::HandleEvent(IEvent* e)
	{
		/*
			Handle registered events
		*/
	}


	bool PhysicsComponent::Initialize()
	{
		/*
			Initialize objects and values and ensure 
			success of memory allocation, etc.
		*/
		return true;
	}


	void PhysicsComponent::Update(float deltaTime)
	{
		/*
			Manage update logic for this component
		*/
	}


	void PhysicsComponent::Shutdown()
	{
		/*
			Release memory and ensure success
		*/
	}


	//////////////////////////
	// Utility Functions
	//////////////////////////
}