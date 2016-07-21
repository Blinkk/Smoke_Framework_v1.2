/**********************************
*  Programmer: Austin Ivicevic
*  Smoke Game Framework v1.2
***********************************/
#include "Engine.h"

namespace Smoke
{
	Direct3D::Direct3D()
	{
		_d3dDevice = nullptr;
		_d3dContext = nullptr;
		_spriteObj = nullptr;
		_backBuffer = nullptr;
	}


	Direct3D::~Direct3D() 
	{
		
	}


	bool Direct3D::Initialize(HINSTANCE hINstance, bool fullScreen, float screenDepth, float screenNear)
	{
		////////////////////////////////////////
		// Initialize Direct3D 9
		////////////////////////////////////////
		// Init pointers
		_d3dDevice = new LPDIRECT3DDEVICE9();
		_d3dContext = new LPDIRECT3D9();
		_spriteObj = new LPD3DXSPRITE();
		_backBuffer = new LPDIRECT3DSURFACE9();

		HRESULT result;

		(*_d3dContext) = Direct3DCreate9(D3D_SDK_VERSION);
		if (!(*_d3dContext))
		{
			debug << "\tUnable to create D3DContext" << std::endl;
			return false;
		}

		// Get system desktop color depth
		D3DDISPLAYMODE dm;
		(*_d3dContext)->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);

		// Set Direct3D presentation parameters
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = (!fullScreen);
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = 1;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.BackBufferFormat = dm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferWidth = SCREENW;
		d3dpp.BackBufferHeight = SCREENH;
		d3dpp.hDeviceWindow = g_Engine->GetWindowHandle();
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;

		// Create Direct3D device
		result = (*_d3dContext)->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_Engine->GetWindowHandle(),
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, _d3dDevice);
		if (result != D3D_OK)
		{
			debug << "\tUnable to create D3DDevice" << std::endl;
			return false;
		}

		// Get a pointer to the back buffer surface
		result = g_Engine->GetDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, _backBuffer);
		if (result != D3D_OK)
		{
			debug << "\tUnable to get pointer to the backbuffer" << std::endl;
			return false;
		}

		// Create sprite object
		result = D3DXCreateSprite(g_Engine->GetDevice(), _spriteObj);
		if (result != D3D_OK)
		{
			debug << "\tUnable to create spriteObj" << std::endl;
			return false;
		}

		/////////////////////
		// Set up matrices
		/////////////////////
		// Setup the projection matrix.
		int fieldOfView = (float)D3DX_PI / 4.0f;
		int screenAspect = (float)SCREENW / (float)SCREENH;

		// Create the projection matrix for 3D rendering
		D3DXMatrixPerspectiveFovLH(&_projMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

		// Initialize the world matrix to identity
		D3DXMatrixIdentity(&_worldMatrix);

		// Create an orthographic projection matrix for 2D rendering
		D3DXMatrixOrthoLH(&_orthoMatrix, (float)SCREENW, (float)SCREENH, screenNear, screenDepth);

		return true;
	}


	void Direct3D::Shutdown()
	{
		// Release memory
		if (_backBuffer)
		{
			if ((*_backBuffer))
			{
				(*_backBuffer)->Release();
			}

			delete _backBuffer;
			_backBuffer = nullptr;
		}
		if (_spriteObj)
		{
			if ((*_spriteObj))
			{
				(*_spriteObj)->Release();
			}

			delete _spriteObj;
			_spriteObj = nullptr;
		}
		if (_d3dContext)
		{
			if ((*_d3dContext))
			{
				(*_d3dContext)->Release();
			}

			delete _d3dContext;
			_d3dContext = nullptr;
		}
		if (_d3dDevice)
		{
			if ((*_d3dDevice))
			{
				(*_d3dDevice)->Release();
			}
			
			delete _d3dDevice;
			_d3dDevice = nullptr;
		}
		
		debug << "\tDirect3D shutdown" << std::endl;
	}


	//////////////////////
	// Utility functions
	//////////////////////
	void Direct3D::ClearScene()
	{
		if (_d3dDevice)
		{
			if ((*_d3dDevice))
			{
				HRESULT result = (*_d3dDevice)->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
					D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
				if (result != D3D_OK)
				{
					debug << "Failed to clear the backbuffer" << std::endl;
					return;
				}
			}
			else
			{
				debug << "Failed to dereference d3dDevice" << std::endl;
				return;
			}
		}
		else
		{
			debug << "Failed to access d3dDevice, pointer is null" << std::endl;
			return;
		}
	}

	void Direct3D::EndScene()
	{
		if (_d3dDevice)
		{
			if ((*_d3dDevice))
			{
				(*_d3dDevice)->EndScene();
				(*_d3dDevice)->Present(nullptr, nullptr, nullptr, nullptr);
			}
			else
			{
				debug << "Failed to dereference d3dDevice" << std::endl;
				return;
			}
		}
		else
		{
			debug << "Failed to access d3dDevice, pointer is null" << std::endl;
			return;
		}
	}


	//////////////////////
	// Accessor functions
	//////////////////////
	LPDIRECT3DDEVICE9& Direct3D::GetDevice()
	{
		return (*_d3dDevice);
	}

	LPDIRECT3D9& Direct3D::GetContext()
	{
		return (*_d3dContext);
	}

	LPD3DXSPRITE& Direct3D::GetSpriteObj()
	{
		return (*_spriteObj);
	}

	LPDIRECT3DSURFACE9& Direct3D::GetBackbuffer()
	{
		return (*_backBuffer);
	}

	void Direct3D::GetWorldMatrix(D3DXMATRIX &wm)
	{
		wm = _worldMatrix;
	}

	void Direct3D::GetProjMatrix(D3DXMATRIX &pm)
	{
		pm = _projMatrix;
	}

	void Direct3D::GetOrthoMatrix(D3DXMATRIX &om)
	{
		om = _orthoMatrix;
	}

}