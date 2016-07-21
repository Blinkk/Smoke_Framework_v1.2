/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "InputComponent.h"

namespace Smoke
{
	InputComponent::InputComponent()
	{
		/*
			Initialize values to default and pointers to null
		*/
		componentType = COMPONENTS::INPUT_COMPONENT;
	}


	InputComponent::~InputComponent()
	{
		/*
			Call shutdown and ensure everything is released
		*/
	}


	void InputComponent::HandleEvent(IEvent* e)
	{
		/*
			Handle registered events
		*/
	}


	bool InputComponent::Initialize()
	{
		/*
			Initialize objects and values and ensure
			success of memory allocation, etc.
		*/

		return true;
	}


	void InputComponent::Update(float deltaTime)
	{
		/*
			Manage update logic for this component
		*/
	}


	void InputComponent::Shutdown()
	{
		/*
			Release memory and ensure success
		*/
	}


	//////////////////////////
	// Utility Functions
	//////////////////////////
}