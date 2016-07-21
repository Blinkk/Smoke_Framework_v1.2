/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "GameManager.h"


///////////////////////////
// Level load functions
///////////////////////////
void Level1()
{
	// Change the camera zoom for this level
	//g_Engine->GetActiveCamera()->SetZoomFactor(0.45f);

	/////////////////////
	// Create Objects
	/////////////////////

	// Update camera position BEFORE loading UI
	//g_Engine->GetActiveCamera()->UpdatePos();

	//////////////////////////////////
	// Load in the map for this level
	//////////////////////////////////
	//g_Manager->GetTileManager()->TileMap(MAPS::LEVEL_ONE_MAP);

	g_Engine->SetShowDebug(true);
}


void Level_MainMenu()
{
	// Change the camera zoom for this level
	//g_Engine->GetActiveCamera()->SetZoomFactor(1.0f);

}


GameManager::GameManager()
{
	endProgram = false;
	gameOver = false;			
	_frameInterval = DEFAULT_FPS;	// Set default fps

	lvlPtr = &Level1;				// Set default level to Main_Menu
	_currentLevel = LEVELS::LEVEL_ONE;	// Set current level
}


GameManager::~GameManager()
{
	// Deallocate memory

}


////////////////////////////////////////
// Initialize game resources
////////////////////////////////////////
bool GameManager::Game_Init()
{
	srand(time(nullptr));

	/////////////////////////
	// Create a camera
	/////////////////////////


	///////////////////////
	// Setup Input devices
	///////////////////////
	Mouse *pMouse = new Mouse();
	if (!pMouse)
	{
		debug << "\tFailed to create a mouse in Game_Init()" << std::endl;
		return false;
	}
	g_Engine->GetInputManager()->SetMouse(pMouse);

	Keyboard *pKeyboard = new Keyboard();
	if (!pKeyboard)
	{
		debug << "\tFailed to create a keyboard in Game_Init()" << std::endl;
		return false;
	}
	g_Engine->GetInputManager()->SetKeyboard(pKeyboard);

	// Key codes
	std::vector<int> codes;
	codes.push_back(DIK_W);			// Move up
	codes.push_back(DIK_A);			// Move left
	codes.push_back(DIK_S);			// Move down
	codes.push_back(DIK_D);			// Move right
	codes.push_back(DIK_SPACE);		// Attack
	codes.push_back(DIK_ESCAPE);	// Open Menu / Exit game
	g_Engine->GetInputManager()->SetDIKKeyboardCodes(codes);

	////////////////////////////
	// Register event listeners
	////////////////////////////

	return true;
}


void GameManager::LoadLevel()
{
	// Call the function that lvlPtr points to
	lvlPtr();

	// Reset the gameOver flag so that the new level can begin
	gameOver = false;
}


void GameManager::UnloadLevel()
{
	// Purge Backgrounds
	g_Engine->GetBackgroundManager()->PurgeBackgrounds();
}


//////////////////////////////////////////////
// Main update function (called in game loop)
//////////////////////////////////////////////
void GameManager::Update(float deltaTime)
{
	//////////////////
	// Update Engine
	//////////////////
	g_Engine->Update(deltaTime);

	// Increment frame count
	g_Engine->IncrementFrameCount();
}


void GameManager::Game_Render()
{
	//////////////////////////////////////////////////////////
	// Clear the backbuffer, render all renderable objects
	// then end the scene and present to game screen
	//////////////////////////////////////////////////////////
	g_Engine->ClearScene();								// Clear the backbuffer for rendering
	if (g_Engine->GetDevice()->BeginScene() == D3D_OK)	// Begin scene
	{
		//// Create a projection matrix
		//_camera->Render();

		//////////////////////////////
		// Begin Spritebatch for 2D
		g_Engine->GetSpriteObj()->Begin(D3DXSPRITE_ALPHABLEND);	// Add object space when using camera...

		g_Engine->GetGraphicsSystem()->Render();

		if (g_Engine->ShowDebug())
			g_Engine->GetDebugger()->Render();

		g_Engine->GetSpriteObj()->End();
		// End Spritebatch for 2D
		//////////////////////////////


		// 3D rendering will go here....

		g_Engine->EndScene();		// End scene and present backbuffer
	}
}


//////////////////////////////////
// Free game specific resources
//////////////////////////////////
void GameManager::Game_End()
{
	
}


//////////////////////
// Utility Functions
//////////////////////
void GameManager::AddGameObject(Handle gameObject)
{
	if (gameObject.m_type == Handle_Types::GAME_OBJECT)
	{
		_gameObjects.push_back(gameObject);
	}
	else
	{
		debug << "Failed to add Game Object to GameManager, wrong type" << std::endl;
		return;
	}
}


void GameManager::RemoveGameObject()
{
	// TODO: Determine how to handle this
}


