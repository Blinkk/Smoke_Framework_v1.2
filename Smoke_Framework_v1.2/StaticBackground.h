/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef STATICBACKGROUND_H
#define STATICBACKGROUND_H
#include "IBackground.h"
#include "Vector.h"

namespace Smoke
{
	class StaticBackground : public IBackground
	{
	private:
		Vector2 _position;

	public:
		StaticBackground();
		~StaticBackground();

		void Initialize(std::string textureToUse,
			float width, float height, Vector2 pos) override;

		void Update(float deltaTime);
		void Render();
	};
}

#endif