/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef IBACKGROUND_H
#define IBACKGROUND_H
#include "TwoDRenderer.h"

namespace Smoke
{
	class IBackground
	{
	protected:
		TwoDRenderer Renderer;

	public:
		virtual ~IBackground() {}

		virtual void Initialize(std::string textureToUse, 
			float width, float height, Vector2 pos) = 0;
	};
}

#endif