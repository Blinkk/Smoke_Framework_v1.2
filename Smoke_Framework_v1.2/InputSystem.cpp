/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "Engine.h"

namespace Smoke
{
	InputSystem::InputSystem()
	{
		systemType = INPUT_SYSTEM;
	}


	InputSystem::~InputSystem()
	{
		// Ensure memory is released
		if (!_inputComponents.empty())
			Shutdown();
	}


	bool InputSystem::Initialize()
	{
		debug << "\tInput System initialized" << std::endl;
		return true;
	}


	void InputSystem::Update(float deltaTime)
	{
		// Call update for each graphics component
		if (!_inputComponents.empty())
		{
			for (_compIt = _inputComponents.begin(); _compIt != _inputComponents.end(); ++_compIt)
			{
				(*_compIt)->Update(deltaTime);
			}
		}
	}


	void InputSystem::Shutdown()
	{
		if (!_inputComponents.empty())
		{
			// Delete each component
			for (_compIt = _inputComponents.begin(); _compIt != _inputComponents.end();)
			{
				delete (*_compIt);
				_compIt = _inputComponents.erase(_compIt);
			}
		}
	}


	void InputSystem::AddComponent(IComponent* pComponent)
	{
		if (pComponent != nullptr)
		{
			// Cast to GraphicsComponent type
			InputComponent* pTemp = nullptr;
			pTemp = dynamic_cast<InputComponent*>(pComponent);

			if (pTemp)
			{
				_inputComponents.push_back(pTemp);
			}
			else
			{
				debug << "Failed to add component to GraphicsSystem, cast unsuccessful" << std::endl;
				return;
			}
		}
		else
		{
			debug << "Failed to add component to GraphicsSystem, component is null" << std::endl;
			return;
		}
	}


	void InputSystem::RemoveComponent(unsigned int componentID)
	{
		for (_compIt = _inputComponents.begin(); _compIt != _inputComponents.end(); ++_compIt)
		{
			if ((*_compIt)->componentID == componentID)
			{
				delete (*_compIt);
				_compIt = _inputComponents.erase(_compIt);
			}
		}
		if (_inputComponents.empty())
			debug << "\tInputSystem shutdown" << std::endl;
		else
			debug << "\tError shutting down InputSystem" << std::endl;
	}
}