/**
* @LC		: 07/02/2020
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


int CVertexBuffer::init() {
	OrigBuffer.init();
	OrigBuffer.setDataDesc(sizeof(SimpleVertex) * 24, D3D11_BIND_VERTEX_BUFFER);

	return 0;
}
