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


int CIndexBuffer::init(DescBuffer inDesc) {
	IndexDB = inDesc;
	OrigBuffer.init();
	OrigBuffer.setDataDesc(IndexDB);

	return 0;
}


D3D11_BUFFER_DESC CIndexBuffer::getBD() {
	return OrigBuffer.getBD();
}

ID3D11Buffer *&CIndexBuffer::getB() {
	return OrigBuffer.getDX11Buffer();
}