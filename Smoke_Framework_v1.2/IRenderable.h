/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef IRENDERABLE_H
#define IRENDERABLE_H

namespace Smoke
{
	class IRenderable
	{
		/*
			Any object that needs to render anything to
			the screen should inherit from this class.
		*/
	public:
		IRenderable() {}
		virtual ~IRenderable() {}

		// Only IRenderable objects and its derivatives should call Render()
		virtual void Render() = 0;
	};
}

#endif