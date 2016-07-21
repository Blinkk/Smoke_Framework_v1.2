/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef DEBUG_H
#define DEBUG_H
#include "Font.h"
#include "Timer.h"

namespace Smoke
{
	class Debug
	{
	private:
		Font _fontObject;
		long _coreFrameRate;
		double _gameTime;
		float _deltaTime;
		Timer _frameTimer;
		
		Debug();

	public:
		
		~Debug();

		static Debug& GetInstance()
		{
			static Debug* pInstance = nullptr;

			if (!pInstance)
			{
				pInstance = new Debug();
			}

			return (*pInstance);
		}

		bool Initialize();
		void Update(float deltaTime);
		void Render();
		void Shutdown();

		//////////////////////
		// Utility functions
		//////////////////////
		void CalcFrameRate();
	};
}

#endif