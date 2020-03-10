/**
* @LC		: 24/02/2020
* @file		: CConstantBuffer.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 12/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CConstantBuffer.h"

CConstantBuffer::CConstantBuffer() {



}

CConstantBuffer::~CConstantBuffer() {



}

int CConstantBuffer::init(DescBuffer inDesc) {
	ConstantDB = inDesc;
	OrigBuffer.init();
	OrigBuffer.setDataDesc(ConstantDB);

	return 0;
}

#ifdef D_DIRECTX
D3D11_BUFFER_DESC CConstantBuffer::getBD() {
	return OrigBuffer.getBD();
}
#endif

void *&CConstantBuffer::getB() {
	return OrigBuffer.getDX11Buffer();
}