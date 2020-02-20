/**
* @LC		: 13/02/2020
* @file		: CTexture2D.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 13/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CTexture2D.h"


CTexture2D::CTexture2D() {
	Texture = NULL;

}


CTexture2D::~CTexture2D() {


}


int CTexture2D::init(TextureDesc inDesc) {
	ZeroMemory(&Desc, sizeof(Desc));
	Desc = inDesc;
	
	Dx11_Desc.Width = Desc.Width;
	Dx11_Desc.Height = Desc.Height;
	Dx11_Desc.MipLevels = Desc.MipLevels;
	Dx11_Desc.ArraySize = Desc.ArraySize;
	Dx11_Desc.Format = Desc.Format;
	Dx11_Desc.SampleDesc = Desc.SampleDesc;
	Dx11_Desc.Usage = Desc.Usage;
	Dx11_Desc.BindFlags = Desc.BindFlags;
	Dx11_Desc.CPUAccessFlags = Desc.CPUAccessFlags;
	Dx11_Desc.MiscFlags = Desc.MiscFlags;
	return 0;
}


ID3D11Texture2D *& CTexture2D::getDXTexture() {
	return Texture;
}


D3D11_TEXTURE2D_DESC CTexture2D::getDXDesc() {
	return Dx11_Desc;
}
