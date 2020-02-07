/**
* @LC		: 07/02/2020
* @file		: CIndexBuffer.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CIndexBuffer.h"


CIndexBuffer::CIndexBuffer() {


}


CIndexBuffer::~CIndexBuffer() {


}


int CIndexBuffer::init() {
	OrigBuffer.init();
	OrigBuffer.setDataDesc(sizeof(WORD) * 36, D3D11_BIND_INDEX_BUFFER);


	return 0;
}
