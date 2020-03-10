/**
* @LC		: 24/02/2020
* @file		: CDeviceContext.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
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
* @brief	: Short description of function.
* @bug		: No Bugs known.
**/
class CDeviceContext {
public: 

	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CDeviceContext();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CDeviceContext();

	/**
	* @brief	: Getter the Device Context.
	* @bug		: No Bugs known.
	**/
	void * & getDContext();

private:
	void * DContext;

};