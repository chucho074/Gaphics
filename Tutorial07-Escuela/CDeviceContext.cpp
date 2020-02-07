/**
* @LC		: 07/02/2020
* @file		: CDeviceContext.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CDeviceContext.h"


CDeviceContext::CDeviceContext() {
	DContext = NULL;

}


CDeviceContext::~CDeviceContext() {


}


ID3D11DeviceContext * &CDeviceContext::getDContext() {

	return DContext;
}