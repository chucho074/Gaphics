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

	Front = normalize(DescCam.lAt - DescCam.pos);
	Right = normalize(cross(DescCam.up_Desc, Front));
	Up = normalize(cross(Front, Right));

	create();


	return 0;
}


mat4x4 CCamera::getPM() {
	return PM;
}


mat4x4 CCamera::getVM() {
	return VM;
}


void CCamera::createPM() {
	PM = perspectiveFovLH(DescCam.Fov, DescCam.W, DescCam.H, DescCam.Near, DescCam.Far);
	
}


void CCamera::createVM() {
	VM = lookAtLH(DescCam.pos, DescCam.lAt, DescCam.up_Desc);
	
}


void CCamera::updatePM() {
	PM = perspectiveFovLH(DescCam.Fov, DescCam.W, DescCam.H, DescCam.Near, DescCam.Far);

}


void CCamera::updateVM() {
	Right = { VM[0][0], VM[0][1], VM[0][2] };
	Up = { VM[1][0], VM[1][1], VM[1][2] };
	Front = { VM[2][0], VM[2][1], VM[2][2] };
	DescCam.lAt = Front + DescCam.pos;
	
}


void CCamera::move(vec3 Tras) {
	if (Tras.x != 0.f) {
		DescCam.pos += (Right * Tras.x);
	}
	if (Tras.y != 0.f) {
		DescCam.pos += (Up * Tras.y);
	}
	if (Tras.z != 0.f) {
		DescCam.pos += (Front * Tras.z);
	}





	mat4 Axis {
		Right.x,	Right.y,	Right.z,	0,
		Up.x,		Up.y,		Up.z,		0,
		Front.x,	Front.y,	Front.z,	0,
		0,			0,			0,			1

	};

	mat4 Pos {
	1,0,0,-DescCam.pos.x,
	0,1,0,-DescCam.pos.y,
	0,0,1,-DescCam.pos.z,
	0,0,0,1
	};
	Pos *= Axis;
	VM = Pos;
	updateVM();
	createVM();
}


void CCamera::update() {
	updateVM();
	updatePM();
}


void CCamera::create() {

	createPM();
	createVM();

}


void CCamera::rotate(vec3 inDir) {
	rotateUp(inDir);
	rotateRight(inDir);
}


void CCamera::rotateUp(vec3 inDir) {
	float camcos = cosf(inDir.x / 100.f);
	float camsin = sinf(inDir.x / 100.f);
	mat4 rotX {
		camcos,		0.f,	camsin,		0.f,
		0.f,		1.f,	0.f,		0.f,
		-camsin,	0.f,	camcos,		0.f,
		0.f,		0.f,	 0.f,		1.f
	};
	VM *= rotX;
	updateVM();

}


void CCamera::rotateRight(vec3 inDir) {
	float camcos = cosf(inDir.y / 100.f);
	float camsin = sinf(inDir.y / 100.f);
	mat4 rotY {
		1.f,		0.f,		0.f,		0.f,
		0.f,		camcos,		-camsin,	0.f,
		0.f,		camsin,		camcos,		0.f,
		0.f,		0.f,		0.f,		1.f
	};
	VM *= rotY;
	updateVM();

}


void CCamera::rotateFront(vec3 inDir) {
	float camcos = cosf(inDir.z / 100.f);
	float camsin = sinf(inDir.z / 100.f);

	mat4 rotZ {
		camcos,		-camsin,		0.f,		0.f,
		camsin,		camcos,			0.f,		0.f,
		0.f,		0.f,			1.f,		0.f,
		0.f,		0.f,			0.f,		1.f
	};
	VM *= rotZ;
	updateVM();
}


//Revisando otra version del proyecto :v = TRUE