/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "Engine.h"
#include "GameManager.h"

namespace Smoke
{
	Factory::Factory()
	{

	}


	Factory::~Factory()
	{

	}


	void Factory::CreateEmptyObject()
	{
		GameObject* emptyGameObject = nullptr;
		if (!emptyGameObject)
		{
			emptyGameObject = new GameObject();
			_gameObjects.push_back(emptyGameObject);
		}
	}


	void Factory::CreateTemplatedObject(unsigned int templateType)
	{
		// Create object/components based on template given
		switch (templateType)
		{
		case TEMPLATES::PLAYER:
			CreatePlayer();
			break;

		default:
			break;

		}
	}


	/////////////////////
	// Templated Objects
	/////////////////////
	void Factory::CreatePlayer()
	{
		// Create object
		GameObject* go = nullptr;
		if (!go) go = new GameObject();

		// Create components and add to object
		EntityComponent* eComp = nullptr;
		if (!eComp)
		{
			eComp = new EntityComponent();
			if (!eComp->Initialize(5, 3))
				debug << "Failed to initialize entity component, did not add to game object" << std::endl;
			else
				g_Engine->GetEntitySystem()->AddComponent(eComp);
		}
		const Handle entityHandle = g_Engine->GetHandleManager()->Add(eComp, Handle_Types::ENTITY_COMPONENT);
		go->AddComponent(entityHandle);
		eComp = nullptr;

		PhysicsComponent* pComp = nullptr;
		if (!pComp)
		{
			pComp = new PhysicsComponent();
			if (!pComp->Initialize())
				debug << "Failed to initialize physics component, did not add to game object" << std::endl;
			g_Engine->GetPhysicsSystem()->AddComponent(pComp);
		}
		const Handle physicsHandle = g_Engine->GetHandleManager()->Add(pComp, Handle_Types::PHYSICS_COMPONENT);
		go->AddComponent(physicsHandle);
		pComp = nullptr;

		InputComponent* iComp = nullptr;
		if (!iComp)
		{
			iComp = new InputComponent();
			if (!iComp->Initialize())
				debug << "Failed to initialize input component, did not add to game object" << std::endl; 
			g_Engine->GetInputSystem()->AddComponent(iComp);
		}
		const Handle inputHandle = g_Engine->GetHandleManager()->Add(iComp, Handle_Types::INPUT_COMPONENT);
		go->AddComponent(inputHandle);
		iComp = nullptr;

		GraphicsComponent* gComp = nullptr;
		if (!gComp)
		{
			gComp = new GraphicsComponent();
			if (!gComp->Initialize(1, 1, 16, 16, 16, 0, 0, 100, 1, 0, SCREENW / 2, SCREENH / 2, "player.png"))
				debug << "Failed to initialize graphics component, did not add to game object" << std::endl;
			else
				g_Engine->GetGraphicsSystem()->AddComponent(gComp);
		}
		const Handle graphicsHandle = g_Engine->GetHandleManager()->Add(gComp, Handle_Types::GRAPHICS_COMPONENT);
		go->AddComponent(graphicsHandle);
		gComp = nullptr;

		// Add GameObject* to Factory vector and a handle to GameManager
		_gameObjects.push_back(go);
		const Handle gameObject = g_Engine->GetHandleManager()->Add(go, Handle_Types::GAME_OBJECT);
		g_Manager->AddGameObject(gameObject);
	}
}