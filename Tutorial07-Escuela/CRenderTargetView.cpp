/**
* @LC		: 16/02/2020
* @file		: CRenderTargetView.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CRenderTargetView.h"


CRenderTargetView::CRenderTargetView() {


}


CRenderTargetView::~CRenderTargetView() {



}


ID3D11RenderTargetView *& CRenderTargetView::getRTV() {
	return RTV;
}
