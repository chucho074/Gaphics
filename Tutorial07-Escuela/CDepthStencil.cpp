/**
* @LC		: 24/02/2020
* @file		: CDephtStencil.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs
**/

/**
* Headers
**/
#include "CDepthStencil.h"


CDepthStencil::CDepthStencil() {


}

CDepthStencil::~CDepthStencil() {


}

int CDepthStencil::init(TextureDesc inDesc) {
	TextureClass.init(inDesc);

	return 0;
}

void *& CDepthStencil::getTexture() {
	return TextureClass.getDXTexture();;
}

#ifdef D_DIRECTX
D3D11_TEXTURE2D_DESC CDepthStencil::getDesc() {
	return TextureClass.getDXDesc();
}
#endif



