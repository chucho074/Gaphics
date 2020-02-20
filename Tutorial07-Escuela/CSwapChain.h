/**
* @LC		: 07/02/2020
* @file		: CSwapChain.h
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
* @brief	: SwapChain Descriptor.
* @bug		: No Bugs known.
**/
struct DescSwapChain {
	
	UINT W;
	UINT H;
	HWND hWnd;
	UINT numerator;
	UINT denominator;
	UINT BufferCount;
	HWND OutputWindow;
	BOOL Windowed;
	UINT count;
	UINT quality;
	DXGI_FORMAT Format;
};


/**
* @brief	: SwapChain Class.
* @bug		: No Bugs known.
**/
class CSwapChain {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CSwapChain();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CSwapChain();

	/**
	* @brief	: Initializer.
	* @param	: DescSwapChain.
	* @bug		: No Bugs known.
	**/
	int init(DescSwapChain);

	/**
	* @brief	: Update.
	* @bug		: No Bugs known..
	**/
	void update();

	/**
	* @brief	: Setter the Width.
	* @param	: UINT.
	* @bug		: No Bugs known.
	**/
	void setWidth(UINT);

	/**
	* @brief	: Setter the Height.
	* @param	: UINT.
	* @bug		: No Bugs known.
	**/
	void setHeight(UINT);

	/**
	* @brief	: Short description of function.
	* @param	: HWHD.
	* @bug		: No Bugs known.
	**/
	void setHwnd(HWND inHwnd);

	/**
	* @brief	: Getter the SwapChain Desc DX.
	* @bug		: No Bugs known.
	**/
	DXGI_SWAP_CHAIN_DESC getSC();

	/**
	* @brief	: Getter the SwapChain DX.
	* @bug		: No Bugs known.
	**/
	IDXGISwapChain *&getSwapC();

private:
	IDXGISwapChain* SwapC;
	DXGI_SWAP_CHAIN_DESC sd;
	UINT W;
	UINT H;
	HWND hWnd;
	DescSwapChain Desc;
};