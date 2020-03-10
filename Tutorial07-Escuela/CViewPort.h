/**
* @LC		: 24/02/2020
* @file		: CViewPort.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 18/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include <windows.h>
#ifdef D_DIRECTX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif

/**
* @brief	: Description for a ViewPort.
* @bug		: No Bugs known.
**/
struct ViewPortDesc {
	float TopLeftX;
	float TopLeftY;
	unsigned int Width;
	unsigned int Height;
	float MinDepth;
	float MaxDepth;
};

/**
* @brief	: Class for ViewPort abstraction.
* @bug		: No Bugs known.
**/
class CViewPort {
public:

	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CViewPort();

	/**
	* @brief	: Destructor of the class.
	* @bug		: No Bugs known.
	**/
	~CViewPort();

	/**
	* @brief	: Init of the class.
	* @param	: ViewPortDesc.
	* @bug		: No Bugs known.
	**/
	int init(ViewPortDesc);

#ifdef D_DIRECTX
	/**
	* @brief	: Getter ViewPort for DX.
	* @bug		: No Bugs known.
	**/
	D3D11_VIEWPORT getDXVP();
#endif
private:
#ifdef D_DIRECTX
	D3D11_VIEWPORT DXVP;
#endif
};

