/**
* @LC		: 07/02/2020
* @file		: CDevice.h
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
* @brief	: CDevice class.
* @bug		: No Bugs known.
**/
class CDevice {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CDevice();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CDevice();

	/**
	* @brief	: Initializer.
	* @bug		: No Bugs known.
	**/
	int init();

	/**
	* @brief	: Update.
	* @bug		: No Bugs known.
	**/
	void update();

	/**
	* @brief	: Render.
	* @bug		: No Bugs known.
	**/
	void render();

	/**
	* @brief	: Destroy.
	* @bug		: No Bugs known.
	**/
	void destroy();

	/**
	* @brief	: Getter the flags DX.
	* @bug		: No Bugs known.
	**/
	UINT getFlags();

	/**
	* @brief	: Getter the device DX.
	* @bug		: No Bugs known.
	**/
	ID3D11Device * & getDevice();

private:
	UINT createDeviceFlags = 0;
	ID3D11Device* Device = NULL;

};