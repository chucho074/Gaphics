/**
* @LC		: 24/02/2020
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
	PS = nullptr;
	PS_Blob = nullptr;

}


CPixelShader::~CPixelShader() {


}


void *& CPixelShader::getPS() {
	return PS;
}


void *& CPixelShader::getPSBlob() {
	return PS_Blob;
}
