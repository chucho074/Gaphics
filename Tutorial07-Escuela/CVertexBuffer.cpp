/**
* @LC		: 24/02/2020
* @file		: CVertexBuffer.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CVertexBuffer.h"


CVertexBuffer::CVertexBuffer() {


}

CVertexBuffer::~CVertexBuffer() {


}

int CVertexBuffer::init(DescBuffer inDesc) {
	VertexBD = inDesc;
	OrigBuffer.init();
	OrigBuffer.setDataDesc(VertexBD);
	
	return 0;
}

#ifdef D_DIRECTX
D3D11_BUFFER_DESC CVertexBuffer::getBD() {
	return OrigBuffer.getBD();
}
#endif

void *& CVertexBuffer::getB() {
	return OrigBuffer.getDX11Buffer();
}
