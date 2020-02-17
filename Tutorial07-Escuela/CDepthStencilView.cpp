/**
* @LC		: 15/02/2020
* @file		: CDepthStencilView.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs
**/

/**
* Headers
**/
#include "CDepthStencilView.h"



CDepthStencilView::CDepthStencilView() {


}


CDepthStencilView::~CDepthStencilView() {


}


int CDepthStencilView::init(DSViewDesc inDesc) {
	ZeroMemory(&descDSV, sizeof(descDSV));
	ZeroMemory(&Desc, sizeof(Desc));
	Desc = inDesc;

	descDSV.Format = Desc.Format;
	descDSV.ViewDimension = Desc.ViewDimension;
	descDSV.Texture2D.MipSlice = Desc.Texture2D.MipSlice;

	return 0;
}

D3D11_DEPTH_STENCIL_VIEW_DESC CDepthStencilView::getDSVDesc() {

	return descDSV;

}

ID3D11DepthStencilView *& CDepthStencilView::getDSV() {
	return DSV;
}
