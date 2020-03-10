/**
* @LC		: 20/02/2020
* @file		: CGraphicsAPI.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 20/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "CDevice.h"
#include "CSwapChain.h"
#include "CDeviceContext.h"

#ifdef D_DIRECTX
class CGraphicsAPI {
public:
	CGraphicsAPI();
	~CGraphicsAPI();
	int init();

private:
	CDevice Device;
	CDeviceContext DC;
	CSwapChain SC;

	DescSwapChain DescSC;


	HWND g_hWnd = NULL;
	D3D_DRIVER_TYPE g_driverType = D3D_DRIVER_TYPE_NULL;

};
#endif
