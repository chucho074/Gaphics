/**
* @LC		: 17/02/2020
* @file		: CCamera.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 16/02/2020
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
#include "CTexture2D.h"

/**
* @brief	: Render Target Class.
* @bug		: No Bugs known.
**/
class CRenderTarget {
public:

	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CRenderTarget();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CRenderTarget();

	/**
	* @brief	: Getter the BackBuffer DX.
	* @bug		: No Bugs known.
	**/
	ID3D11Texture2D *& getBB();

private:

	CTexture2D * BackBuffer;

};

