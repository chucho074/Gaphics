/**
* @LC		: 19/02/2020
* @file		: CPixelShader.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 19/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CPixelShader.h"


CPixelShader::CPixelShader() {
	PS = NULL;
	PS_Blob = NULL;

}


CPixelShader::~CPixelShader() {


}


ID3D11PixelShader *& CPixelShader::getPS() {
	return PS;
}


ID3DBlob *& CPixelShader::getPSBlob() {
	return PS_Blob;
}
