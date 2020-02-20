/**
* @LC		: 19/02/2020
* @file		: CVertexShader.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 19/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CVertexShader.h"


CVertexShader::CVertexShader() {
	VS = NULL;
	VS_Blob = NULL;
}


CVertexShader::~CVertexShader() {


}


ID3D11VertexShader *&CVertexShader::getVS() {
	return VS;
}


ID3DBlob *& CVertexShader::getVSBlob() {
	return VS_Blob;
}

