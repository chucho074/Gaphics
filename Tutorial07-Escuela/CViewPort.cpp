/**
* @LC		: 18/02/2020
* @file		: CViewPort.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 18/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CViewPort.h"


CViewPort::CViewPort() {


}


CViewPort::~CViewPort() {


}


int CViewPort::init(ViewPortDesc inDesc) {

	DXVP.TopLeftX = inDesc.TopLeftX;
	DXVP.TopLeftY = inDesc.TopLeftY;
	DXVP.Width = inDesc.Width;
	DXVP.Height = inDesc.Height;
	DXVP.MinDepth = inDesc.MinDepth;
	DXVP.MaxDepth = inDesc.MaxDepth;

	return 0;
}


D3D11_VIEWPORT CViewPort::getDXVP() {
	return DXVP;
}
