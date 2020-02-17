/**
* @LC		: 07/02/2020
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


}


CSwapChain::~CSwapChain() {


}


int CSwapChain::init(DescSwapChain inDescSC) {
	
	Desc = inDescSC;
	SwapC = NULL;

	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = Desc.BufferCount;
	sd.BufferDesc.Width = Desc.W;
	sd.BufferDesc.Height = Desc.H;
	sd.BufferDesc.Format = Desc.Format;
	sd.BufferDesc.RefreshRate.Numerator = Desc.numerator;
	sd.BufferDesc.RefreshRate.Denominator = Desc.denominator;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Desc.OutputWindow;
	sd.SampleDesc.Count = Desc.count;
	sd.SampleDesc.Quality = Desc.quality;
	sd.Windowed = Desc.Windowed;

	return 0;

}


void CSwapChain::update() {
	
}


void CSwapChain::setWidth(UINT inWidth) {
	W = inWidth;
}


void CSwapChain::setHeight(UINT inHeight) {
	H = inHeight;
}


void CSwapChain::setHwnd(HWND inHwnd) {
	hWnd = inHwnd;
}


DXGI_SWAP_CHAIN_DESC CSwapChain::getSC() {
	return sd;
}


IDXGISwapChain *&CSwapChain::getSwapC() {
	return SwapC;
}