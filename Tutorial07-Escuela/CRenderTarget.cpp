/**
* @LC		: 17/02/2020
* @file		: CRenderTargetView.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 16/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CRenderTarget.h"


CRenderTarget::CRenderTarget() {
	BackBuffer = new CTexture2D();

}


CRenderTarget::~CRenderTarget() {


}


ID3D11Texture2D *& CRenderTarget::getBB() {
	return BackBuffer->getDXTexture();
}