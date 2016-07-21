/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "StaticBackground.h"
#include "Engine.h"

namespace Smoke
{
	StaticBackground::StaticBackground()
	{

	}


	StaticBackground::~StaticBackground()
	{

	}


	void StaticBackground::Initialize(std::string textureToUse, 
		float width, float height, Vector2 pos)
	{
		// Initialize the background renderer
		Renderer.Initialize(1.0f, 1.0f, width, height, 1, 0,
			0, 0, 0, 0.0f, pos.x, pos.y, textureToUse);
	}


	void StaticBackground::Update(float deltaTime)
	{

	}


	void StaticBackground::Render()
	{
		if (Renderer.HasTexture())
			Renderer.Render();
	}
}