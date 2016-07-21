/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#pragma once
////////////////////////////////////////
// Global Defines
////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN

#define APPTITLE "King's Truth"

// Screen parameters
#define SCREEN_DEPTH 1.0f
#define SCREEN_NEAR 0.0f
#define SCREENW 800
#define SCREENH 608

// Default FPS
#define DEFAULT_FPS 60

////////////////////////////////////////
// Include Libraries 
////////////////////////////////////////
#include <Windows.h>
#include <iostream>
#include <vector>

#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "D3Dcompiler.lib")
#pragma comment (lib, "dxerr")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma warning (disable : 4244)
#pragma warning (disable : 4018)
#pragma warning (disable : 4800)


////////////////////////////////////////
// Include systems/managers header files
////////////////////////////////////////
#include "GraphicsSystem.h"
#include "EntitySystem.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "EventManager.h"
#include "HandleManager.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "BackgroundManager.h"
#include "UISystem.h"
#include "Factory.h"
#include "Direct3D.h"
#include "Camera2D.h"
#include "Debug.h"
#include "LogFile.h"
#include "Vector.h"


///////////////////////////
// Engine Class - Smoke
///////////////////////////
namespace Smoke
{
	class Engine
	{
	private:
		/*
			Since we are using a vector here, the order in which
			the systems are pushed back into the vector is the
			order in which they will update. Therefore, they
			should be pushed into the vector in the following
			order:
				* Input_System		
				* Physics_System	
				* Entity_System
				* Graphics_System	
		*/
		std::vector<ISystem*> _systems;				// Systems to be managed by engine
		std::vector<ISystem*>::iterator _systemIt;	// Iterator into vector of systems

		/////////////////////
		// DirectX Object
		/////////////////////
		Direct3D* _directX;							// DirectX wrapper object

		/////////////////////
		// Factory Object
		/////////////////////
		Factory* _factory;							// Pointer to factory instance

		/////////////////////
		// Global references
		/////////////////////
		Camera2D* _camera;							// Pointer to main camera object

		///////////////
		// Managers
		///////////////
		EventManager* _eventManager;				// Pointer to event manager object
		HandleManager* _handleManager;				// Pointer to handle manager object
		InputManager* _inputManager;				// Pointer to input manager object
		TextureManager* _textureManager;			// Pointer to texture manager object
		BackgroundManager* _backgroundManager;		// Pointer to background manager object

		Debug* _debugger;							// Pointer to debug object
		HWND _hwnd;									// Handle to window that game is using
		Timer _gameTimer;							// Main game timer
		bool _showDebug;							// Flag to show debugger
		unsigned int _coreFrameCount;				// Frame count

		Engine();

	public:
		static Engine& GetInstance()
		{
			Engine* pInstance = nullptr;
			if (!pInstance)
			{
				pInstance = new Engine();
			}

			return (*pInstance);
		}

		~Engine();

		////////////////////////////
		// Engine Core Functions
		////////////////////////////
		bool Initialize(HINSTANCE hInstance, bool fullScreen);
		void Update(float deltaTime);
		void Render();
		void Shutdown();		


		////////////////////////////
		// Utility Functions
		////////////////////////////
		void ClearScene();
		void EndScene();
		void IncrementFrameCount();
		void ResetFrameCount();


		//////////////////////////////
		// Accessor functions
		//////////////////////////////
		Factory* GetFactory();					// Return a pointer to Factory instance
		Camera2D* GetActiveCamera();			// Return a pointer to Camera object
		InputSystem* GetInputSystem();			// Return a pointer to InputSystem
		PhysicsSystem* GetPhysicsSystem();		// Return a pointer to PhysicsSystem
		EntitySystem* GetEntitySystem();		// Return a pointer to EntitySystem
		GraphicsSystem* GetGraphicsSystem();	// Return a pointer to GraphicsSystem
		UISystem* GetUISystem();				// Return a pointer to UISystem
		EventManager* GetEventManager();		// Return a pointer to EventManager
		HandleManager* GetHandleManager();		// Return a pointer to HandleManager
		InputManager* GetInputManager();		// Return a pointer to input manager
		TextureManager* GetTextureManager();	// Return a pointer to texture manager
		BackgroundManager* GetBackgroundManager();	// Return a pointer to background manager
		Debug* GetDebugger();					// Return a pointer to debug object

		LPDIRECT3DDEVICE9& GetDevice();			// Return a reference to D3DDEVICE
		LPDIRECT3D9& GetContext();				// Return a reference to D3D_Context
		LPD3DXSPRITE& GetSpriteObj();			// Return a reference to sprite object
		LPDIRECT3DSURFACE9& GetBackbuffer();	// Return a reference to the backbuffer
		HWND& GetWindowHandle();				// Return a reference to window handle

		unsigned int GetFrameCount();			// Return current frame count
		double GetGameTime();					// Return elapsed game time from main timer
		bool ShowDebug();						// Return flag to display debugger info

		//////////////////////////////
		// Mutator Functions
		//////////////////////////////
		void SetShowDebug(bool value);			// Set flag to display debugger info
		
		
	};	// End of class
}	// End of namespace

extern std::auto_ptr<Smoke::Engine> g_Engine;	// Global engine object pointer