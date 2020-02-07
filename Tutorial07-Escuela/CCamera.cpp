/**
* @LC		: 07/02/2020
* @file		: CCamera.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CCamera.h"




CCamera::CCamera() {

}



CCamera::~CCamera() {

}



int CCamera::init(DescCamera inDesc) {

	DescCam = inDesc;
	DescCam.pos = { 0.0f, 3.0f, -6.0f };
	DescCam.lAt = { 0.0f, 1.0f, 0.0f };
	DescCam.up_Desc = { 0.0f, 1.0f, 0.0f };



	createVM();
	createPM();


	return 0;
}




XMMATRIX CCamera::getPM() {
	return PM;
}



XMMATRIX CCamera::getVM() {
	return VM;
}



void CCamera::createPM() {
	//PM = XMMatrixPerspectiveFovLH(DescCam.Fov, (DescCam.W / DescCam.H), DescCam.Near, DescCam.Far);
}




void CCamera::createVM() {
	VM = XMMatrixLookAtLH(DescCam.pos, DescCam.lAt, DescCam.up_Desc);
}



void CCamera::move(XMFLOAT3) {


}

