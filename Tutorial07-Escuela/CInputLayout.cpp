/**
* @LC		: 19/02/2020
* @file		: CInputLayout.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 19/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CInputLayout.h"


CInputLayout::CInputLayout() {
	IL = NULL;
}


CInputLayout::~CInputLayout() {

}


ID3D11InputLayout *& CInputLayout::getIL() {

	return IL;
}
