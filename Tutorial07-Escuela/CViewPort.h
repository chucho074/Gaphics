/**
* @LC		: 18/02/2020
* @file		: CViewPort.cpp
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
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"

/**
* @brief	: Description for a ViewPort.
* @bug		: No Bugs known.
**/
struct ViewPortDesc {
	float TopLeftX;
	float TopLeftY;
	float Width;
	float Height;
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

	/**
	* @brief	: Getter ViewPort for DX.
	* @bug		: No Bugs known.
	**/
	D3D11_VIEWPORT getDXVP();
private:
	D3D11_VIEWPORT DXVP;
};

