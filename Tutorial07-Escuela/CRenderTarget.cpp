/**
* @LC		: 24/02/2020
* @file		: CRenderTarget.h
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


void *& CRenderTarget::getBB() {
	return BackBuffer->getDXTexture();
}