/**
* @LC		: 24/02/2020
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
	DSV = nullptr;

}

CDepthStencilView::~CDepthStencilView() {


}

int CDepthStencilView::init(DSViewDesc inDesc) {
#ifdef D_DIRECTX
	ZeroMemory(&descDSV, sizeof(descDSV));
	ZeroMemory(&Desc, sizeof(Desc));
	Desc = inDesc;

	descDSV.Format = (DXGI_FORMAT)Desc.Format;
	descDSV.ViewDimension = (D3D11_DSV_DIMENSION)Desc.ViewDimension;
	descDSV.Texture2D.MipSlice = Desc.Texture2D;
#endif
	return 0;
}

#ifdef D_DIRECTX
D3D11_DEPTH_STENCIL_VIEW_DESC CDepthStencilView::getDSVDesc() {

	return descDSV;
}
#endif

void *& CDepthStencilView::getDSV() {
	return DSV;
}
