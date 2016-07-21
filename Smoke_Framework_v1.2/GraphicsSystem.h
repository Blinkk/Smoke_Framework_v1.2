/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H
#include "ISystem.h"
#include "GraphicsComponent.h"

namespace Smoke
{
	class GraphicsSystem : public ISystem, public IRenderable
	{
	private:
		std::vector<GraphicsComponent*> _graphicsComponents;	// Vector of graphics components to manage
		std::vector<GraphicsComponent*>::iterator _compIt;		// Iterator into vector of components

		GraphicsSystem();

	public:
		static GraphicsSystem& GetInstance()
		{
			GraphicsSystem* pInstance = nullptr;
			if (!pInstance)
			{
				pInstance = new GraphicsSystem();
			}

			return (*pInstance);
		}

		~GraphicsSystem();

		// Render <-- IMPORTANT
		void Render() override;

		bool Initialize() override;
		void Update(float deltaTime) override;
		void Shutdown() override;
		void AddComponent(IComponent* pComponent) override;
		void RemoveComponent(unsigned int componentID) override;
	};	
}

#endif