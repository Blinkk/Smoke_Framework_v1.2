/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef FACTORY_H
#define FACTORY_H
#include "GameObject.h"
#include <vector>

enum TEMPLATES
{
	PLAYER = 0,
};

namespace Smoke
{
	class Factory
	{
	private:
		std::vector<GameObject*> _gameObjects;

		Factory();

		/////////////////////
		// Templated Objects
		/////////////////////
		void CreatePlayer();

	public:
		static Factory& GetInstance()
		{
			Factory* pInstance = nullptr;

			if (!pInstance)
			{
				pInstance = new Factory();
			}

			return (*pInstance);
		}

		~Factory();

		/*
			These object creation functions should be used
			to create all game objects and their components
			in the entire game. Upon creation components should be
			stored in their respective systems and GameObjects
			should be given Handles to them. Additionally, handles
			to the GameObjects themselves should be stored in the
			GameManager class.
		*/
		void CreateEmptyObject();
		void CreateTemplatedObject(unsigned int templateType);
	};
}

#endif