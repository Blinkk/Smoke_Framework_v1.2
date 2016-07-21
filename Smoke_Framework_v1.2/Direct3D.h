/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#ifndef DIRECTX_H
#define DIRECTX_H
#include "stdafx.h"


//////////////////////////////
// Note: This code leaks both
// the d3dDevice and Context
// and needs to be fixed.
//////////////////////////////

namespace Smoke
{
	class Direct3D
	{
	private:
		LPDIRECT3DDEVICE9 *_d3dDevice;				// DirectX device
		LPDIRECT3D9 *_d3dContext;					// DirectX context
		LPD3DXSPRITE *_spriteObj;					// Sprite object
		LPDIRECT3DSURFACE9 *_backBuffer;			// Backbuffer pointer
		D3D_DRIVER_TYPE _driverType;				// Graphics card driver type
		D3D_FEATURE_LEVEL _featureLevel;			// Feature level for D3D
		D3DXMATRIX _projMatrix;						// Projection matrix
		D3DXMATRIX _worldMatrix;					// World matrix
		D3DXMATRIX _orthoMatrix;					// Orthagraphic matrix (for 2D)

		Direct3D();

	public:
		static Direct3D& GetInstance()
		{
			Direct3D *pInstance = nullptr;

			if (!pInstance)
			{
				pInstance = new Direct3D();
			}

			return (*pInstance);
		}

		~Direct3D();
		bool Initialize(HINSTANCE hInstance, 
			bool fullScreen, float screenDepth, float screenNear);
		void Shutdown();

		//////////////////////
		// Utility functions
		//////////////////////
		void ClearScene();
		void EndScene();


		//////////////////////////////
		// Accessor/Mutator functions
		//////////////////////////////
		LPDIRECT3DDEVICE9& GetDevice();
		LPDIRECT3D9& GetContext();
		LPD3DXSPRITE& GetSpriteObj();
		LPDIRECT3DSURFACE9& GetBackbuffer();
		void GetWorldMatrix(D3DXMATRIX &wm);
		void GetProjMatrix(D3DXMATRIX &pm); 
		void GetOrthoMatrix(D3DXMATRIX &om);
	};
}

#endif