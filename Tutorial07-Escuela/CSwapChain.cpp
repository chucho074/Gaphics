/**
* @LC		: 24/02/2020
* @file		: CSwapChain.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CSwapChain.h"


CSwapChain::CSwapChain() {
	SwapC = nullptr;
	
}


CSwapChain::~CSwapChain() {


}


int CSwapChain::init(DescSwapChain inDescSC) {
	
	Desc = inDescSC;
	SwapC = NULL;

#ifdef D_DIRECTX
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = Desc.BufferCount;
	sd.BufferDesc.Width = Desc.W;
	sd.BufferDesc.Height = Desc.H;
	sd.BufferDesc.Format = ((DXGI_FORMAT)Desc.Format);
	sd.BufferDesc.RefreshRate.Numerator = Desc.numerator;
	sd.BufferDesc.RefreshRate.Denominator = Desc.denominator;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Desc.OutputWindow;
	sd.SampleDesc.Count = Desc.count;
	sd.SampleDesc.Quality = Desc.quality;
	sd.Windowed = Desc.Windowed;
#endif

	return 0;

}


void CSwapChain::update() {
	
}


void CSwapChain::setWidth(unsigned int inWidth) {
	W = inWidth;
}


void CSwapChain::setHeight(unsigned int inHeight) {
	H = inHeight;
}


void CSwapChain::setHwnd(HWND inHwnd) {
	hWnd = inHwnd;
}


void *&CSwapChain::getSwapC() {
	return SwapC;
}

#ifdef D_DIRECTX
DXGI_SWAP_CHAIN_DESC CSwapChain::getSC() {
	return sd;
}
#endif