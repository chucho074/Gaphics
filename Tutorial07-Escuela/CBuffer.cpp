/**
* @LC		: 12/02/2020
* @file		: CBuffer.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A base class for Buffers.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CBuffer.h"


CBuffer::CBuffer() {


}


CBuffer::~CBuffer() {

	//delete PBuffer;
}


int CBuffer::init() {
	PBuffer = NULL;

	ZeroMemory(&bd, sizeof(bd));
	return 0;
}


void CBuffer::updateData() {
	//bd_DX.Usage = bd.Usage;
	bd_DX.ByteWidth = bd.ByteWidth;
	bd_DX.BindFlags = bd.BindFlags;
	//bd_DX.CPUAccessFlags = bd.CPUAccessFlags;
}


ID3D11Buffer *& CBuffer::getBuffer() {
	return PBuffer;
}


void CBuffer::setDataDesc(DescBuffer inDescBuff) {
	/*bd.Usage = inUsage;
	bd.ByteWidth = inByte;
	bd.BindFlags = inFlags;
	bd.CPUAccessFlags = inCpuF;*/
	bd = inDescBuff;
	updateData();
}


D3D11_BUFFER_DESC CBuffer::getBD() {
	return bd_DX;
}

ID3D11Buffer *&CBuffer::getDX11Buffer() {
	return PBuffer;
}


