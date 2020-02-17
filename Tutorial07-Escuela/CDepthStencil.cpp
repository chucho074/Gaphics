
#include "CDepthStencil.h"


CDepthStencil::CDepthStencil() {


}


CDepthStencil::~CDepthStencil() {


}


int CDepthStencil::init(TextureDesc inDesc) {
	TextureClass.init(inDesc);

	return 0;
}


ID3D11Texture2D *& CDepthStencil::getTexture() {
	return TextureClass.getDXTexture();;
}


D3D11_TEXTURE2D_DESC CDepthStencil::getDesc() {
	return TextureClass.getDXDesc();
}



