/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef UI_H
#define UI_H
#include "ISystem.h"
#include "IRenderable.h"
#include "UIComponent.h"
#include <vector>

enum UI_LEVELS
{
	STANDARD_GAMEPLAY_UI = 0,
	MAIN_MENU_UI
};

/*
	This enum is merely to avoid having to include the entire contents
	of the GameManager.h when all we need access to is the LEVELS enum.
	
	Note: This enum must match the one in the GameManager.h in order to function
	properly.
	
	TODO: Make this make more sense....
*/
enum GAME_LEVELS
{
	GAME_LEVEL_MAIN_MENU = 0,
	GAME_LEVEL_ONE = 1,
};

namespace Smoke
{
	class UISystem : public ISystem, IRenderable
	{
	private:
		UISystem();
		std::vector<UIComponent*> _uiComponents;
		std::vector<UIComponent*>::iterator _compIt;

	public:
		static UISystem& GetInstance()
		{
			UISystem *pInstance = nullptr;

			if (!pInstance)
			{
				pInstance = new UISystem();
			}

			return (*pInstance);
		}

		~UISystem();

		/*
			This function calls the render function for
			each UIObject in the vector.

			Note: UI elements will not render if there is no
			active camera set in the global reference. (g_Engine->SetActiveCamera(...))
		*/
		void Render() override;

		bool Initialize() override;
		void Update(float deltaTime) override;
		void Shutdown() override;


		//////////////////////
		// Utility Functions
		//////////////////////
		void DrawDebug();
		void AddComponent(IComponent* pComponent) override;
		void RemoveComponent(unsigned int componentID) override;
	};
}

#endif