/**
* @LC		: 29/01/2020
* @file		: CCamera.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/01/2020
* @brief	: This class have all about the camera.
* @bug		: No Bugs.
**/

/**
* Headers
*/
#include "CCamera.h"

/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
CCamera::CCamera() {
	front = {0.0f,0.0f,0.0f};
	up = { 0.0f,0.0f,0.0f };
	right = { 0.0f,0.0f,0.0f };
	
}

/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
CCamera::~CCamera() {

}

/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
int CCamera::init(CCameraDesc cam) {
	Desc = cam;
	
	front = { (getlAt(Desc) - getPos(Desc)) };	//z
	right = { (cross(getUp(Desc),(front))) };	//x
	up = { (cross(front,right)) };				//y

	front = normalize(front);
	right = normalize(right);
	up = normalize(up);

	//VM = lookAtLH(Desc.pos,Desc.lAt,Desc.up_Desc);
	updateVM();
	updatePM();
	return 0;
}

/**
* @brief	: Update the View Matrix.
* @bug		: No Bugs known.
**/
void CCamera::updateVM() {

	right = { VM[0][0], VM[0][1], VM[0][2] };
	up = { VM[1][0], VM[1][1], VM[1][2] };
	front = { VM[2][0], VM[2][1], VM[2][2] };
	//Desc.lAt = front + Desc.pos;
	VM = ViewMatrixCreate();
}

/**
* @brief	: Update the Perspective Matrix.
* @bug		: No Bugs known.
**/
void CCamera::updatePM() {
	PM = PerspectiveMatrixFovLH(Desc.Fov, Desc.W / Desc.H,Desc.Near,Desc.Far);
}

/**
* @brief	: Rotation in X (Pitch).
* @param	: The angle.
* @bug		: No Bugs known.
**/
void CCamera::rotPitch(float RotX) {
	
	//mat4 Rot (1.f);
	VM = rotate(VM, RotX, {0, 1, 0});
	//M = (VM * Rot);
	updateVM();
	
}

/**
* @brief	: Rotation in Y (Yaw).
* @param	: The angle.
* @bug		: No Bugs known.
**/
void CCamera::rotYaw(float RotY) {

	//mat4 Rot(1.f);
	VM = rotate(VM, RotY, {1,0,0});
	//VM *= Rot;
	updateVM();
	

}

/**
* @brief	: Rotation in Z (Rol).
* @param	: The angle.
* @bug		: No Bugs known.
**/
void CCamera::rotRoll(float RotZ) {

	//mat4 Rot (1.f);
	VM = rotate(VM, RotZ, {0, 0, 1});
	//VM = (VM * Rot);
	updateVM();
	

}

/**
* @brief	: The movement of the camera.
* @param	: Needs a vector of the movement.
* @bug		: No Bugs known.
**/
void CCamera::move(vec3 Tras) {
	Desc.pos += (right	* Tras.x);
	Desc.pos += (up		* Tras.y);
	Desc.pos += (front	* Tras.z);
	
	VM = lookAt(Desc.pos, Desc.lAt, Desc.up_Desc);
	updateVM();
}

/**
* @brief	: Create the View Matrix.
* @bug		: No Bugs known.
**/
mat4 CCamera::ViewMatrixCreate() {
	
	return translate(mat4(1.f),-Desc.pos);
}

/**
* @brief	: Create the Perspective Matrix.
* @param	: FOV, Aspect Ration, Near, Far.
* @bug		: No Bugs known.
**/
mat4 CCamera::PerspectiveMatrixFovLH(float inFov, float inAR, float inNearZ, float inFarZ) {

	return perspectiveFovLH(inFov, Desc.W, Desc.H, inNearZ, inFarZ);
}



/////////////////////////////////////////
//////////SETTERS & GETTERS//////////////
/////////////////////////////////////////

/**
* @brief	: Sets the position vector.
* @param	: Needs a vector 3 for the position.
* @bug		: No Bugs known.
**/
void CCamera::setPos(vec3 posCam) {
	Desc.pos = posCam;
}

/**
* @brief	: Sets the Look At vector.
* @param	: Needs a vector 3 for the LookAt.
* @bug		: No Bugs known.
**/
void CCamera::setlAt(vec3 lAtCam) {
	Desc.lAt = lAtCam;
}

/**
* @brief	: Sets the up vector.
* @param	: Needs a vector 3 for the Up.
* @bug		: No Bugs known.
**/
void CCamera::setUp(vec3 upCam) {
	up = upCam;
}

/**
* @brief	: Sets the Width.
* @param	: Needs a float for the Width.
* @bug		: No Bugs known.
**/
void CCamera::setWidth(float Width) {
	Desc.W = Width;
}

/**
* @brief	: Sets the Height.
* @param	: Needs a float for the Height.
* @bug		: No Bugs known.
**/
void CCamera::setHeight(float Height) {
	Desc.H = Height;
}

/**
* @brief	: Sets the FOV.
* @param	: Needs a float for the FOV.
* @bug		: No Bugs known.
**/
void CCamera::setFov(float FOV) {
	Desc.Fov = FOV;
}

/**
* @brief	: Sets the Near distance.
* @param	: Needs a float for	Near distance.
* @bug		: No Bugs known.
**/
void CCamera::setNear(float Near) {
	Desc.Near = Near;
}

/**
* @brief	: Sets the far distance.
* @param	: Needs a float for Far distance.
* @bug		: No Bugs known.
**/
void CCamera::setFar(float Far) {
	Desc.Far = Far;
}

/**
* @brief	: Getter the Position.
* @param	: Needs a CameraDescription.
* @bug		: No Bugs known.
**/
vec3 CCamera::getPos(CCameraDesc cam) {
	return cam.pos;
}

/**
* @brief	: Getter the LookAt.
* @param	: Needs a CameraDescription.
* @bug		: No Bugs known.
**/
vec3 CCamera::getlAt(CCameraDesc cam) {
	return cam.lAt;
}

/**
* @brief	: Short description of function.
* @param	: Needs a CameraDescription.
* @bug		: No Bugs known.
**/
vec3 CCamera::getUp(CCameraDesc cam) {
	return cam.up_Desc;
}

/**
* @brief	: Getter View Matrix.
* @bug		: No Bugs known.
**/
mat4 CCamera::getVM() {
	return VM;
}

/**
* @brief	: Getter Perspective Matrix.
* @bug		: No Bugs known.
**/
mat4 CCamera::getPM() {
	return PM;
}


void CCamera::MoveMouse(vec3 Dir) {
	RotMouse(Dir);
	updateVM();
	
}

void CCamera::RotMouse(vec3 Dir) {
	RotMouseX(Dir);
	updateVM();
	RotMouseY(Dir);
	VM = ViewMatrixCreate();
}


void CCamera::RotMouseX(vec3 Dir) {
	float cosine = cosf(Dir.x / 100);
	float sine = sinf(Dir.x / 100);
	mat4 rot;
	//float speed = 0.10f;
	rot = {
		cosine,	0.0f,	sine,	0.0f,
		0.0f, 1.0f,	0.0f, 0.0f,
		-sine,   0.0f,	cosine,	0.0f,
		0.0f, 0.0f,   0.0f,			1.0f
	};
	VM *= rot;
	
	
	//updateVM();
}


void CCamera::RotMouseY(vec3 Dir)
{
	float cosine = cosf(Dir.y / 100);
	float sine = sinf(Dir.y / 100);
	mat4 rot;
	rot = {
			 1.0f, 0.0f,  0.0f, 0.0f,
			0.0f,  cosine, -sine, 0.0f,
			0.0f,  sine,  cosine, 0.0f,
			0.0f,    0.0f,   0.0f, 1.0f
	};
	VM *= rot;
	//updateVM();
	VM = ViewMatrixCreate();
}