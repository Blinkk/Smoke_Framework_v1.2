/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H
#include "IComponent.h"
#include "IRenderable.h"
#include "TwoDRenderer.h"
#include "Font.h"

enum UI_COMPONENTS
{
	UI_BUTTON = 0,
	UI_LABEL = 1,
	UI_PICBOX = 2
};

namespace Smoke
{
	class UIComponent : public IComponent, public IRenderable
	{
	private:
		TwoDRenderer* _renderer;	// Renderer to handle UI textures/animations
		Font _fontObject;			// Font object to show text on button
		std::string _text;			// Text to display on button
		D3DXCOLOR _textColor;		// Color of button text

		// Dimensions
		float _width;
		float _height;

		// Flag to show/unshow UI_Component
		bool _active;

		/////////////////////
		// UI Component Type
		/////////////////////
		unsigned int _uiComponentType;

		//////////////////////////
		// Utility Functions
		//////////////////////////
		/*
			Internal functions used to streamline code
		*/

	public:
		UIComponent();
		~UIComponent();

		// Render <-- IMPORTANT
		void Render() override;

		void HandleEvent(IEvent* e) override;
		bool Initialize(float scaleX, float scaleY, unsigned int frameWidth,
			unsigned int frameHeight, unsigned int numCol,
			unsigned int startFrame, unsigned int endFrame,
			unsigned int delay, int animDirection, unsigned int uiComponentType,
			float rotationInRadians, float newX, float newY, bool active = true,
			std::string textureToUse = "", std::string text = "", D3DCOLOR textColor = D3DCOLOR_XRGB(255,255,255));
		void Update(float deltaTime) override;
		void Shutdown() override;

	};
}

#endif