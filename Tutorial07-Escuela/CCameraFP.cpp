#include "CCameraFP.h"

CCameraFP::CCameraFP() {


}

CCameraFP::~CCameraFP() {


}

int CCameraFP::init(DescCameraFP inDesc) {

	ZeroMemory(&DescCam, sizeof(DescCam));
	DescCam = inDesc;
	DescCam.pos = { 0.0f, 3.0f, -6.0f };
	DescCam.lAt = { 0.0f, 1.0f, 0.0f };
	DescCam.up_Desc = { 0.0f, 1.0f, 0.0f };

	Front = normalize(DescCam.lAt - DescCam.pos);
	Right = normalize(cross(DescCam.up_Desc, Front));
	Up = normalize(cross(Front, Right));

	createVM();
	updatePM();


	return 0;
}

void CCameraFP::update() {
	updateVM();
	updatePM();

}

mat4x4 CCameraFP::getPM() {
	return PM;
}

void CCameraFP::create() {
	updatePM();
	createVM();

}

mat4x4 CCameraFP::getVM() {
	return VM;
}

void CCameraFP::createVM() {
	mat4 Axis = { Right.x,	Right.y,	Right.z,	0,
			Up.x,		Up.y,		Up.z,		0,
			Front.x,	Front.y,	Front.z,	0,
			0,			0,			0,			1 };

	mat4 Pos = { 1,0,0,-DescCam.pos.x,
			0,1,0,-DescCam.pos.y,
			0,0,1,-DescCam.pos.z,
			0,0,0,1 };

	Pos *= Axis;		//Crear matriz vista

	VM = Pos;

}

void CCameraFP::updatePM() {
	PM = perspectiveFovLH(DescCam.Fov, DescCam.W, DescCam.H, DescCam.Near, DescCam.Far);

}

void CCameraFP::updateVM() {
	Right = { VM[0][0], VM[0][1], VM[0][2] };
	Up = { VM[1][0], VM[1][1], VM[1][2] };
	Front = { VM[2][0], VM[2][1], VM[2][2] };
	DescCam.lAt = Front + DescCam.pos;

}

void CCameraFP::move(vec3 Tras) {
	if (Tras.x != 0.f) {
		DescCam.pos += (Right * Tras.x);
	}
	if (Tras.y != 0.f) {
		DescCam.pos += (Up * Tras.y);
	}
	if (Tras.z != 0.f) {
		DescCam.pos += (Front * Tras.z);
	}
	Right = normalize(Right);
	Up = normalize(Up);
	Front = normalize(Front);

	mat4 Axis{
		Right.x,	Right.y,	Right.z,	0,
		Up.x,		Up.y,		Up.z,		0,
		Front.x,	Front.y,	Front.z,	0,
		0,			0,			0,			1

	};

	mat4 Pos{
	1,0,0,-DescCam.pos.x,
	0,1,0,-DescCam.pos.y,
	0,0,1,-DescCam.pos.z,
	0,0,0,1
	};
	Pos *= Axis;
	VM = Pos;
	createVM();

}

void CCameraFP::rotate(vec3 inDir) {
	
	if (xAngle != 25.f) {
		rotateRight(inDir);
	}
	if (yAngle != 80.f || yAngle != -20.f) {
		rotateUp(inDir);
	}
	rotateFront(inDir);
	
}

void CCameraFP::rotateUp(vec3 inDir) {
	xAngle += inDir.x;
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

void CCameraFP::rotateRight(vec3 inDir) {
	yAngle += inDir.y;
	float camcos = cosf(inDir.y / 100.f);
	float camsin = sinf(inDir.y / 100.f);
	mat4 rotY{
		1.f,		0.f,		0.f,		0.f,
		0.f,		camcos,		-camsin,	0.f,
		0.f,		camsin,		camcos,		0.f,
		0.f,		0.f,		0.f,		1.f
	};
	VM *= rotY;
	updateVM();

}

void CCameraFP::rotateFront(vec3 inDir) {
	float camcos = cosf(inDir.z / 100.f);
	float camsin = sinf(inDir.z / 100.f);

	mat4 rotZ{
		camcos,		-camsin,		0.f,		0.f,
		camsin,		camcos,			0.f,		0.f,
		0.f,		0.f,			1.f,		0.f,
		0.f,		0.f,			0.f,		1.f
	};
	VM *= rotZ;
	updateVM();

}

void CCameraFP::updateSize(unsigned int inW, unsigned int inH) {
	DescCam.W = inW;
	DescCam.H = inH;
	//update();

}
