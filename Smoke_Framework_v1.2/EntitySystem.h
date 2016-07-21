/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H
#include "ISystem.h"
#include "EntityComponent.h"

namespace Smoke
{
	class EntitySystem : public ISystem
	{
	private:
		std::vector<EntityComponent*> _entityComponents;// Vector of entity component pointers
		std::vector<EntityComponent*>::iterator _compIt;// Iterator into vector of component pointers

		EntitySystem();

	public:
		static EntitySystem& GetInstance()
		{
			EntitySystem* pInstance = nullptr;
			if (!pInstance)
			{
				pInstance = new EntitySystem();
			}

			return (*pInstance);
		}

		~EntitySystem();

		bool Initialize() override;
		void Update(float deltaTime) override;
		void Shutdown() override;
		void AddComponent(IComponent* pComponent) override;
		void RemoveComponent(unsigned int componentID) override;
	};
}

#endif