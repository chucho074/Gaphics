/**
* @LC		: 24/02/2020
* @file		: CDevice.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CDevice.h"


CDevice::CDevice() {


}


CDevice::~CDevice() {


}


int CDevice::init() {
#ifdef D_DIRECTX
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	Device = nullptr;
#endif

	return 0;
}


void CDevice::update() {


}


void CDevice::render() {


}


void CDevice::destroy() {


}


unsigned int CDevice::getFlags() {
	return createDeviceFlags;
}


void * &CDevice::getDevice() {

	return Device;
}