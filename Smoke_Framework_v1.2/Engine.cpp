/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "Engine.h"

namespace Smoke
{
	Engine::Engine()
	{
		// Default values
		_directX = nullptr;
		_factory = nullptr;
		_camera = nullptr;
		_eventManager = nullptr;
		_handleManager = nullptr;
		_inputManager = nullptr;
		_textureManager = nullptr;
		_backgroundManager = nullptr;
		_debugger = nullptr;

		_coreFrameCount = 0;
		_showDebug = false;
	}


	Engine::~Engine()
	{
		// Ensure memory has been released
		if (!_systems.empty())
			Shutdown();
	}


	bool Engine::Initialize(HINSTANCE hInstance, bool fullScreen)
	{
		debug << "Initializing engine..." << std::endl;

		//////////////////////
		// Initialize DirectX
		//////////////////////
		_directX = &Direct3D::GetInstance();
		if (!_directX)
		{
			debug << "\tFailed to create Direct3D instance" << std::endl;
			return false;
		}
		else if (!_directX->Initialize(hInstance, fullScreen, SCREEN_DEPTH, SCREEN_NEAR))
		{
			debug << "\tFailed to initialize Direct3D" << std::endl;
			return false;
		}

		//////////////////////
		// Initialize Factory
		//////////////////////
		_factory = &Factory::GetInstance();
		if (!_factory)
		{
			debug << "\tFailed to create Factory instance" << std::endl;
			return false;
		}

		//////////////////////
		// Initialize Camera
		//////////////////////
		_camera = new Camera2D();
		if (!_camera)
		{
			debug << "\tFailed to initialize camera" << std::endl;
			return false;
		}
			
		////////////////////
		// Create systems
		////////////////////
		// Input System
		InputSystem* pTempSystem_Input = &InputSystem::GetInstance();
		if (pTempSystem_Input)
			_systems.push_back(pTempSystem_Input);
		else
		{
			debug << "\tFailed to create InputSystem instance" << std::endl;
			return false;
		}

		// Physics System
		PhysicsSystem* pTempSystem_Physics = &PhysicsSystem::GetInstance();
		if (pTempSystem_Physics)
			_systems.push_back(pTempSystem_Physics);
		else
		{
			debug << "\tFailed to create PhysicsSystem instance" << std::endl;
			return false;
		}

		// Entity System
		EntitySystem* pTempSystem_Entity = &EntitySystem::GetInstance();
		if (pTempSystem_Entity)
			_systems.push_back(pTempSystem_Entity);
		else
		{
			debug << "\tFailed to create EntitySystem instance" << std::endl;
			return false;
		}

		// Graphics System
		GraphicsSystem* pTempSystem_Graphics = &GraphicsSystem::GetInstance();
		if (pTempSystem_Graphics)
			_systems.push_back(pTempSystem_Graphics);
		else
		{
			debug << "\tFailed to create GraphicsSystem instance" << std::endl;
			return false;
		}

		// UI System
		UISystem* pTempSystem_UI = &UISystem::GetInstance();
		if (pTempSystem_UI)
			_systems.push_back(pTempSystem_UI);
		else
		{
			debug << "\tFailed to create UISystem instance" << std::endl;
			return false;
		}

		//////////////////////////
		// Initialize all systems
		//////////////////////////
		for (_systemIt = _systems.begin(); _systemIt != _systems.end(); ++_systemIt)
		{
			if (!(*_systemIt)->Initialize())
			{
				debug << "\tFailed to initialize system, Type: " << (SYSTEMS)(*_systemIt)->systemType << std::endl;
				return false;
			}
		}

		/////////////////////////////
		// Create and init managers
		/////////////////////////////
		// Event manager
		_eventManager = &EventManager::GetInstance();
		if (!_eventManager)
		{
			debug << "\tFailed to create EventManager" << std::endl;
			return false;
		}

		// Handle manager
		_handleManager = &HandleManager::GetInstance();
		if (!_handleManager)
		{
			debug << "\tFailed to create HandleManager" << std::endl;
			return false;
		}

		// Input manager
		_inputManager = &InputManager::GetInstance();
		if (!_inputManager)
		{
			debug << "\tFailed to create InputManager" << std::endl;
			return false;
		}
		else if (!_inputManager->Initialize())
		{
			debug << "\tFailed to initialize InputManager" << std::endl;
			return false;
		}

		// Texture manager
		_textureManager = &TextureManager::GetInstance();
		if (!_textureManager)
		{
			debug << "\tFailed to create TextureManager" << std::endl;
			return false;
		}
		else if (!_textureManager->Initialize())
		{
			debug << "\tFailed to initialize TextureManager" << std::endl;
			return false;
		}

		// Background manager
		_backgroundManager = &BackgroundManager::GetInstance();
		if (!_backgroundManager)
		{
			debug << "\tFailed to create TextureManager" << std::endl;
			return false;
		}

		// Debugger
		_debugger = &Debug::GetInstance();
		if (!_debugger)
		{
			debug << "\tFailed to create Debug instance" << std::endl;
			return false;
		}
		else if (!_debugger->Initialize())
		{
			debug << "\tFailed to initialize Debug instance" << std::endl;
			return false;
		}

		debug << "Engine initialized successfully" << std::endl;
		return true;
	}


	void Engine::Update(float deltaTime)
	{
		// Update all systems
		for (_systemIt = _systems.begin(); _systemIt != _systems.end(); ++_systemIt)
		{
			(*_systemIt)->Update(deltaTime);
		}

		// Update managers that require updates
		_inputManager->Update(deltaTime);
		_debugger->Update(deltaTime);

		// Update camera position
		// TODO: Change this
		//_camera->UpdatePos();
	}


	void Engine::Render()
	{
		// Create a projection matrix using camera object
		_camera->Render();

		// Render systems that can render
		for (_systemIt = _systems.begin(); _systemIt != _systems.end(); ++_systemIt)
		{
			IRenderable* pTemp = nullptr;
			pTemp = dynamic_cast<IRenderable*>((*_systemIt));

			if (pTemp)
				pTemp->Render();
		}
	}


	void Engine::Shutdown()
	{
		debug << "Shutting down engine..." << std::endl;

		// Shutdown all systems
		for (_systemIt = _systems.begin(); _systemIt != _systems.end();)
		{
			// Call system's shutdown
			(*_systemIt)->Shutdown();

			// Delete the system
			delete (*_systemIt);
			_systemIt = _systems.erase(_systemIt);
		}

		// Shutdown managers that require shutdown
		if (_debugger)
		{
			delete _debugger;
			_debugger = nullptr;
		}
		if (_backgroundManager)
		{
			delete _backgroundManager;
			_backgroundManager = nullptr;
		}
		if (_textureManager)
		{
			_textureManager->Shutdown();
			delete _textureManager;
			_textureManager = nullptr;
		}
		if (_inputManager)
		{
			_inputManager->Shutdown();
			delete _inputManager;
			_inputManager = nullptr;
		}
		if (_handleManager)
		{
			// TODO: Shutdown, release handles...
			delete _handleManager;
			_handleManager = nullptr;
		}
		if (_eventManager)
		{
			_eventManager->Shutdown();
			delete _eventManager;
			_eventManager = nullptr;
		}
		if (_camera)
		{
			delete _camera;
			_camera = nullptr;
		}

		// Shutdown factory
		if (_factory)
		{
			delete _factory;
			_factory = nullptr;
		}

		// Shutdown DirectX
		if (_directX)
		{
			_directX->Shutdown();
			delete _directX;
			_directX = nullptr;
		}

		debug << "Engine shutdown successfully!" << std::endl;
	}


	//////////////////////
	// Utility functions
	//////////////////////
	void Engine::ClearScene()
	{
		if (_directX)
			_directX->ClearScene();
		else
		{
			debug << "Failed to access Direct3D instance, pointer is null" << std::endl;
			return;
		}
	}

	void Engine::EndScene()
	{
		if (_directX)
			_directX->EndScene();
		else
		{
			debug << "Failed to access Direct3D instance, pointer is null" << std::endl;
			return;
		}
	}

	void Engine::IncrementFrameCount()
	{
		++_coreFrameCount;
	}

	void Engine::ResetFrameCount()
	{
		_coreFrameCount = 0;
	}



	//////////////////////////////
	// Accessor functions
	//////////////////////////////
	Factory* Engine::GetFactory()
	{
		if (_factory)
		{
			return _factory;
		}
		else
		{
			debug << "Failed to get pointer to factory, pointer is null" << std::endl;
			return nullptr;
		}
	}

	Camera2D* Engine::GetActiveCamera()
	{
		if (_camera)
		{
			return _camera;
		}
		else
		{
			debug << "Failed to get pointer to camera, pointer is null" << std::endl;
			return nullptr;
		}			
	}

	InputSystem* Engine::GetInputSystem()
	{
		for (_systemIt = _systems.begin(); _systemIt != _systems.end(); ++_systemIt)
		{
			if ((*_systemIt)->systemType == INPUT_SYSTEM)
			{
				InputSystem* pTemp = nullptr;
				pTemp = dynamic_cast<InputSystem*>((*_systemIt));

				if (pTemp)
					return pTemp;
				else
				{
					debug << "Failed to cast system to correct type (INPUT_SYSTEM)" << std::endl;
					return nullptr;
				}
			}
		}

		debug << "Failed to retrieve system (INPUT_SYSTEM), no system of this type exists" << std::endl;
		return nullptr;
	}

	PhysicsSystem* Engine::GetPhysicsSystem()
	{
		for (_systemIt = _systems.begin(); _systemIt != _systems.end(); ++_systemIt)
		{
			if ((*_systemIt)->systemType == PHYSICS_SYSTEM)
			{
				PhysicsSystem* pTemp = nullptr;
				pTemp = dynamic_cast<PhysicsSystem*>((*_systemIt));

				if (pTemp)
					return pTemp;
				else
				{
					debug << "Failed to cast system to correct type (PHYSICS_SYSTEM)" << std::endl;
					return nullptr;
				}
			}
		}

		debug << "Failed to retrieve system (PHYSICS_SYSTEM), no system of this type exists" << std::endl;
		return nullptr;
	}

	EntitySystem* Engine::GetEntitySystem()
	{
		for (_systemIt = _systems.begin(); _systemIt != _systems.end(); ++_systemIt)
		{
			if ((*_systemIt)->systemType == ENTITY_SYSTEM)
			{
				EntitySystem* pTemp = nullptr;
				pTemp = dynamic_cast<EntitySystem*>((*_systemIt));

				if (pTemp)
					return pTemp;
				else
				{
					debug << "Failed to cast system to correct type (ENTITY_SYSTEM)" << std::endl;
					return nullptr;
				}
			}
		}

		debug << "Failed to retrieve system (ENTITY_SYSTEM), no system of this type exists" << std::endl;
		return nullptr;
	}

	GraphicsSystem* Engine::GetGraphicsSystem()
	{
		for (_systemIt = _systems.begin(); _systemIt != _systems.end(); ++_systemIt)
		{
			if ((*_systemIt)->systemType == GRAPHICS_SYSTEM)
			{
				GraphicsSystem* pTemp = nullptr;
				pTemp = dynamic_cast<GraphicsSystem*>((*_systemIt));

				if (pTemp)
					return pTemp;
				else
				{
					debug << "Failed to cast system to correct type (GRAPHICS_SYSTEM)" << std::endl;
					return nullptr;
				}
			}
		}

		debug << "Failed to retrieve system (GRAPHICS_SYSTEM), no system of this type exists" << std::endl;
		return nullptr;
	}

	UISystem* Engine::GetUISystem()
	{
		for (_systemIt = _systems.begin(); _systemIt != _systems.end(); ++_systemIt)
		{
			if ((*_systemIt)->systemType == UI_SYSTEM)
			{
				UISystem* pTemp = nullptr;
				pTemp = dynamic_cast<UISystem*>((*_systemIt));

				if (pTemp)
					return pTemp;
				else
				{
					debug << "Failed to cast system to correct type (GRAPHICS_SYSTEM)" << std::endl;
					return nullptr;
				}
			}
		}

		debug << "Failed to retrieve system (UI_SYSTEM), no system of this type exists" << std::endl;
		return nullptr;
	}

	EventManager* Engine::GetEventManager()
	{
		if (_eventManager)
		{
			return _eventManager;
		}
		else
		{
			debug << "Failed to get pointer to event manager, pointer is null" << std::endl;
			return nullptr;
		}
	}

	HandleManager* Engine::GetHandleManager()
	{
		if (_handleManager)
		{
			return _handleManager;
		}
		else
		{
			debug << "Failed to get pointer to handle manager, pointer is null" << std::endl;
			return nullptr;
		}
	}

	InputManager* Engine::GetInputManager()
	{
		if (_inputManager)
			return _inputManager;
		else
		{
			debug << "Failed to get pointer to input manager, pointer is null" << std::endl;
			return nullptr;
		}
	}

	TextureManager* Engine::GetTextureManager()
	{
		if (_textureManager)
			return _textureManager;
		else
		{
			debug << "Failed to get pointer to texture manager, pointer is null" << std::endl;
			return nullptr;
		}
	}

	BackgroundManager* Engine::GetBackgroundManager()
	{
		if (_backgroundManager)
			return _backgroundManager;
		else
		{
			debug << "Failed to get pointer to background manager, pointer is null" << std::endl;
			return nullptr;
		}
	}

	LPDIRECT3DDEVICE9& Engine::GetDevice()
	{
		 return _directX->GetDevice();
	}

	LPDIRECT3D9& Engine::GetContext()
	{
		return _directX->GetContext();
	}

	LPD3DXSPRITE& Engine::GetSpriteObj()
	{
		return _directX->GetSpriteObj();
	}

	LPDIRECT3DSURFACE9& Engine::GetBackbuffer()
	{
		return _directX->GetBackbuffer();
	}

	Debug* Engine::GetDebugger()
	{
		if (_debugger)
			return _debugger;
		else
		{
			debug << "Failed to get pointer to debugger, pointer is null" << std::endl;
			return nullptr;
		}
	}

	HWND& Engine::GetWindowHandle()
	{
		return _hwnd;
	}

	unsigned int Engine::GetFrameCount()
	{
		return _coreFrameCount;
	}

	double Engine::GetGameTime()
	{
		return _gameTimer.GetElapsed();
	}

	bool Engine::ShowDebug()
	{
		return _showDebug;
	}

	void Engine::SetShowDebug(bool value)
	{
		_showDebug = value;
	}
}