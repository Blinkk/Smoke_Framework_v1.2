#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H
#include "ISystem.h"
#include "InputComponent.h"

namespace Smoke
{
	class InputSystem : public ISystem
	{
	private:
		std::vector<InputComponent*> _inputComponents;	// Vector of pointers to input components
		std::vector<InputComponent*>::iterator _compIt;	// Iterator into vector of component pointers

		InputSystem();

	public:
		static InputSystem& GetInstance()
		{
			InputSystem* pInstance = nullptr;

			if (!pInstance)
			{
				pInstance = new InputSystem();
			}

			return (*pInstance);
		}

		~InputSystem();

		bool Initialize() override;
		void Update(float deltaTime) override;
		void Shutdown() override;
		void AddComponent(IComponent* pComponent) override;
		void RemoveComponent(unsigned int componentID) override;
	};
}

#endif