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


int CSwapChain::init() {
	SwapC = NULL;

	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	return 0;

}



void CSwapChain::update() {
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = W;
	sd.BufferDesc.Height = H;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
}


void CSwapChain::setWidth(UINT inWidth) {
	W = inWidth;
	update();
}


void CSwapChain::setHeight(UINT inHeight) {
	H = inHeight;
	update();
}


void CSwapChain::setHwnd(HWND inHwnd) {
	hWnd = inHwnd;
	update();
}


DXGI_SWAP_CHAIN_DESC CSwapChain::getSC() {
	return sd;
}


IDXGISwapChain *&CSwapChain::getSwapC() {
	return SwapC;
}