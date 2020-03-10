/**
* @LC		: 24/02/2020
* @file		: CVertexShader.h
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
#ifdef D_DIRECTX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif


/**
* @brief	: Class for Vertex Shader abstraction.
* @bug		: No Bugs known.
**/
class CVertexShader {
public:

	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CVertexShader();

	/**
	* @brief	: Destructor of the class.
	* @bug		: No Bugs known.
	**/
	~CVertexShader();

	/**
	* @brief	: Getter for VertexShader DX.
	* @bug		: No Bugs known.
	**/
	void *& getVS();

	/**
	* @brief	: Getter for the Blob DX.
	* @bug		: No Bugs known.
	**/
	void *& getVSBlob();
private:

	void * VS;
	void * VS_Blob;
};