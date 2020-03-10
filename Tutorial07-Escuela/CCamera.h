/**
* @LC		: 07/02/2020
* @file		: CCamera.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#pragma once
#include <windows.h>
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective

using namespace glm;



/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
struct DescCamera {
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
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Al mover la camara primero se buguea y si se mueve primero no.
**/
class CCamera {
public:
	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CCamera();

	/**
	* @brief	: Destroy of the class.
	* @bug		: No Bugs known.
	**/
	~CCamera();

	/**
	* @brief	: Initializer.
	* @param	: Needs a Camera Description.
	* @bug		: No Bugs known.
	**/
	int init(DescCamera);

	/**
	* @brief	: Update.
	* @param	: Needs a Camera Description.
	* @bug		: No Bugs known.
	**/
	void update();

private:
	DescCamera DescCam;

	vec3 Front;
	vec3 Right;
	vec3 Up;

	mat4x4 PM;
	mat4x4 VM;

	float xAngle = 0;
	float yAngle = 0;
public:
	vec3 initPos;
	vec3 endPos;
	vec3 dir;
	bool mouseClicked;
public:

	/**
	* @brief	: Getter for the Projection Matrix.
	* @bug		: No Bugs known.
	**/
	mat4x4 getPM();

	void create();

	/**
	* @brief	: Getter for the View Matrix.
	* @bug		: No Bugs known.
	**/
	mat4x4 getVM();

	/**
	* @brief	: Create the View Matrix.
	* @bug		: No Bugs known.
	**/
	void createVM();

	/**
	* @brief	: Create the Projection Matrix.
	* @bug		: Can't use it 4 create de PM, have a error from the Lib.
	**/
	void updatePM();

	/**
	* @brief	: Create the View Matrix.
	* @bug		: No Bugs known.
	**/
	void updateVM();

	/**
	* @brief	: Move the VM.
	* @param	: .
	* @bug		: No Bugs known.
	**/
	void move(vec3);

	/**
	* @brief	: Rotate the VM.
	* @param	: .
	* @bug		: No Bugs known.
	**/
	void rotate(vec3);

	/**
	* @brief	: Rotate the VM.
	* @param	: .
	* @bug		: No Bugs known.
	**/
	void rotateUp(vec3);

	/**
	* @brief	: Rotate the VM.
	* @param	: .
	* @bug		: No Bugs known.
	**/
	void rotateRight(vec3);

	/**
	* @brief	: Rotate the VM.
	* @param	: .
	* @bug		: No Bugs known.
	**/
	void rotateFront(vec3);


	void updateSize(unsigned int, unsigned int);

};

