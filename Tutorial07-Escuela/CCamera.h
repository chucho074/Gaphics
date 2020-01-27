/**
* @LC		: 24/01/2020
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
#pragma once
#include "Includes.h"

/**
* @brief	: Struct for every camera.
* @bug		: No Bugs.
*/
struct CCameraDesc {
	
	vec3 pos;
	vec3 lAt;
	vec3 up_Desc; //Del mundo
	float W = 0.f;
	float H = 0.f;
	float Fov = 0.f;
	float Near = 0.f;
	float Far = 0.f;

};

/**
* @brief	: The main class for the camera.
* @bug		: No Bugs.
*/
class CCamera {
public: 
	CCamera();
	~CCamera();
private:
	vec3 front;
	vec3 up;
	vec3 right;
	mat4 VM;
	mat4 PM;
	mat4 Axis;
	mat4 Pos;
	

	CCameraDesc Desc;
	
	vec3 EyeDirection;
	
public:
	
	int init(CCameraDesc cam);
	void updateVM();
	void updatePM();
	void move(vec3);
	void rotPitch(float);
	void setPos(vec3 posCam);
	void setlAt(vec3 posCam);
	void setUp(vec3 posCam);
	void setWidth(float);
	void setHeight(float);
	void setFov(float);
	void setNear(float);
	void setFar(float);

	vec3 getPos(CCameraDesc);
	vec3 getlAt(CCameraDesc);
	vec3 getUp(CCameraDesc);

	mat4 getVM();
	mat4 getPM();

	mat4 ViewMatrixCreate();
	mat4 PerspectiveMatrixFovLH(float, float, float, float);
};