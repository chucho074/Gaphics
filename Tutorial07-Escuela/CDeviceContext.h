/**
* @LC		: 07/02/2020
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
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"

/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/

class CDeviceContext {
public: 

	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	CDeviceContext();

	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	~CDeviceContext();

	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	ID3D11DeviceContext * & getDContext();

private:
	ID3D11DeviceContext* DContext;



};

