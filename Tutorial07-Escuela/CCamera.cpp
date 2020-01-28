/**
* @LC		: 26/01/2020
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
	up  = normalize(up);
	
	updateVM();
	updatePM();
	return 0;
}

/**
* @brief	: Update the View Matrix.
* @bug		: No Bugs known.
**/
void CCamera::updateVM() {

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
	
	mat4 Rot;
	rotate(Rot,RotX,front);
	VM = (VM * Rot);
	updateVM();
	
}

/**
* @brief	: The movement of the camera.
* @param	: Needs a vector of the movement.
* @bug		: No Bugs known.
**/
void CCamera::move(vec3 Tras) {
	Desc.pos += (right * Tras.x);
	Desc.pos += (up * Tras.y);
	Desc.pos += (front * Tras.z);
	updateVM();
}

/**
* @brief	: Create the View Matrix.
* @bug		: No Bugs known.
**/
mat4 CCamera::ViewMatrixCreate() {
return glm::lookAtLH(Desc.pos, Desc.lAt, Desc.up_Desc);
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

