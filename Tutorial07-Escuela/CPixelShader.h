/**
* @LC		: 19/02/2020
* @file		: CInputLayout.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 19/02/2020
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
* @brief	: Class for Pixel Shader abstraction.
* @bug		: No Bugs known.
**/
class CPixelShader {
public:

	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CPixelShader();

	/**
	* @brief	: Destructor of the class.
	* @bug		: No Bugs known.
	**/
	~CPixelShader();

	/**
	* @brief	: Getter the PixelShader DX.
	* @bug		: No Bugs known.
	**/
	ID3D11PixelShader *& getPS();

	/**
	* @brief	: Getter the Pixel Shader Blob.
	* @bug		: No Bugs known.
	**/
	ID3DBlob *& getPSBlob();
private:
	ID3D11PixelShader * PS;
	ID3DBlob * PS_Blob;
};

