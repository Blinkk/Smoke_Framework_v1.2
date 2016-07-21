/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H
#include "IComponent.h"
#include "TwoDRenderer.h"
#include "IRenderable.h"

namespace Smoke
{
	class GraphicsComponent : public IComponent, public IRenderable
	{
	private:
		/*
			Stores variables, objects to be managed by physics component
		*/
		TwoDRenderer *_renderer;

		//////////////////////////
		// Utility Functions
		//////////////////////////
		/*
			Internal functions used to streamline code
		*/

	public:
		GraphicsComponent();
		~GraphicsComponent();

		// Render <-- IMPORTANT
		void Render() override;

		void HandleEvent(IEvent* e) override;
		bool Initialize(float scaleX, float scaleY, unsigned int frameWidth,
			unsigned int frameHeight, unsigned int numCol,
			unsigned int startFrame, unsigned int endFrame,
			unsigned int delay, int animDirection,
			float rotationInRadians, float newX, float newY,
			std::string textureToUse);
		void Update(float deltaTime) override;
		void Shutdown() override;
	};
}

#endif