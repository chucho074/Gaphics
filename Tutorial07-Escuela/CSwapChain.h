/**
* @LC		: 24/02/2020
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
#ifdef D_DIRECTX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif


/**
* @brief	: SwapChain Descriptor.
* @bug		: No Bugs known.
**/
struct DescSwapChain {
	
	unsigned int W;
	unsigned int H;
	HWND hWnd;
	unsigned int numerator;
	unsigned int denominator;
	unsigned int BufferCount;
	HWND OutputWindow;
	bool Windowed;
	unsigned int count;
	unsigned int quality;
	short Format;
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
	void setWidth(unsigned int);

	/**
	* @brief	: Setter the Height.
	* @param	: UINT.
	* @bug		: No Bugs known.
	**/
	void setHeight(unsigned int);

	/**
	* @brief	: Short description of function.
	* @param	: HWHD.
	* @bug		: No Bugs known.
	**/
	void setHwnd(HWND inHwnd);

	/**
	* @brief	: Getter the SwapChain DX.
	* @bug		: No Bugs known.
	**/
	void *&getSwapC();

#ifdef D_DIRECTX
	/**
	* @brief	: Getter the SwapChain Desc DX.
	* @bug		: No Bugs known.
	**/
	DXGI_SWAP_CHAIN_DESC getSC();
#endif
private:
	void * SwapC;
	unsigned int W;
	unsigned int H;
	HWND hWnd;
	DescSwapChain Desc;
#ifdef D_DIRECTX
	DXGI_SWAP_CHAIN_DESC sd;
#endif
};
