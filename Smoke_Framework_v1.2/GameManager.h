/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Engine.h"
#include "Handle.h"
#include "Keyboard.h"
#include "Mouse.h"
//#include "StaticBackground.h"
//#include "TileManager.h"
#include <Windows.h>
using namespace Smoke;

enum LEVELS
{
	LEVEL_MAIN_MENU = 0,
	LEVEL_ONE = 1,
};

////////////////////////
// Game Manager class 
////////////////////////
class GameManager
{
private:
	unsigned int _frameInterval;
	std::vector<Handle> _gameObjects;							// Vector of handles to GameObjects
	std::vector<Handle>::iterator _handleIt;					// Iterator into vector of GameObjects handles

	/*
		Keeps track of the currently active level, so that we can go back into
		it if the player dies. Also used to make sure we don't reload the same
		assets unnecessarily.
	*/
	unsigned int _currentLevel;

	/*
		A function pointer that is used to load the necessary assets needed for
		a given level.
	 
		The level functions are defined in GameManager.cpp, and are kept seperate from
		the Game Object so that GameManager doesn't need to have a function for every
		possible level. This allows us to easily add/remove levels without modifying
		too much code.
	*/
	void(*lvlPtr)();

	// Constructor
	GameManager();

public:
	///////////////////
	// Public variables
	///////////////////
	bool endProgram;
	bool gameOver;

	///////////////////
	// Game functions
	///////////////////
	static GameManager& GetInstance()
	{
		GameManager *pInstance = nullptr;
		if (!pInstance)
		{
			pInstance = new GameManager();
		}

		return (*pInstance);
	}

	virtual ~GameManager();

	bool Game_Init();						// Initialize game specifics
	void Update(float deltaTime);			// Main update call
	void Game_Render();						// Render game
	void Game_End();						// Release game objects in level


	/*
		This function is just a wrapper for levelPointer, and only serves to
		disallow direct access to the function pointer itself.

		This function just calls whatever levelPointer points to.
	*/
	void LoadLevel();


	/*
		This function is used to release all objects
		for a single level to allow for loading of objects
		for a new level. This should be called only from
		the end of the "Level Loop" in Windows.cpp
	*/
	void UnloadLevel();


	//////////////////////
	// Utility functions
	//////////////////////
	void AddGameObject(Handle gameObject);
	void RemoveGameObject();

	//////////////////////////////
	// Accessor/Mutator Functions
	//////////////////////////////
	//TileManager* GetTileManager() { return _tileManager; }
	const unsigned int GetFrameInterval() { return _frameInterval; }
	void SetFrameInterval(unsigned int newFrameInterval) { _frameInterval = newFrameInterval; }
	unsigned int GetCurrentLevel() { return _currentLevel; }
};
#endif

extern std::auto_ptr<GameManager> g_Manager;	// Global GameManager object

