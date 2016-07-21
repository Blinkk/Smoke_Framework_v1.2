/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include "ISystem.h"
#include "PhysicsComponent.h"

namespace Smoke
{
	class PhysicsSystem : public ISystem
	{
	private:
		std::vector<PhysicsComponent*> _physicsComponents;	// Vector of physics component pointers
		std::vector<PhysicsComponent*>::iterator _compIt;	// Iterator into vector of component pointers

		PhysicsSystem();

	public:
		static PhysicsSystem& GetInstance()
		{
			PhysicsSystem* pInstance = nullptr;

			if (!pInstance)
			{
				pInstance = new PhysicsSystem();
			}

			return (*pInstance);
		}

		~PhysicsSystem();

		bool Initialize() override;
		void Update(float deltaTime) override;
		void Shutdown() override;
		void AddComponent(IComponent* pComponent) override;
		void RemoveComponent(unsigned int componentID) override;
	};
}

#endif