/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H
#include "IComponent.h"

/*
	This component simply serves as an
	event handler for input events. These
	events will be dispatched from the 
	input manager.
*/
namespace Smoke
{
	class InputComponent : public IComponent
	{
	public:
		InputComponent();
		~InputComponent();

		void HandleEvent(IEvent* e) override;
		bool Initialize();
		void Update(float deltaTime) override;
		void Shutdown() override;
	};
}

#endif
