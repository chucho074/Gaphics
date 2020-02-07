/**
* @LC		: 07/02/2020
* @file		: CBuffer.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CBuffer.h"

CBuffer::CBuffer() {


}


CBuffer::~CBuffer() {

	delete PBuffer;
}


int CBuffer::init() {
	PBuffer = NULL;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;
	return 0;
}

ID3D11Buffer *& CBuffer::getBuffer() {
	return PBuffer;
}

void CBuffer::setDataDesc(UINT inByte, UINT inFlags) {
	bd.ByteWidth = inByte;
	bd.BindFlags = inFlags;
}


