/**
* @LC		: 24/02/2020
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
	IL = nullptr;
}


CInputLayout::~CInputLayout() {

}


void *& CInputLayout::getIL() {

	return IL;
}
