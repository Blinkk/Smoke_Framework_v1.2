/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "Handle.h"
#include <vector>

namespace Smoke
{
	class GameObject
	{
	private:
		/*
			Game Objects store handles to their components
			whose pointers are actually stored in the
			system that will manage their updates, etc.
		*/
		std::vector<Handle> _components;
		std::vector<Handle>::iterator _handleIt;

	public:
		GameObject();
		~GameObject();

		void AddComponent(Handle component);
		void RemoveComponent(unsigned int componentType);
	};
}

#endif