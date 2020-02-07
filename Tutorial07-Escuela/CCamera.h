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
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"


/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
struct DescCamera {
	XMVECTOR pos;
	XMVECTOR lAt;
	XMVECTOR up_Desc; //Del mundo
	FLOAT W = 0.f;
	FLOAT H = 0.f;
	FLOAT Fov = 0.f;
	FLOAT Near = 0.f;
	FLOAT Far = 0.f;
};

/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
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

private:
	DescCamera DescCam;

	XMFLOAT3 Front;
	XMFLOAT3 Right;
	XMFLOAT3 Up;

	XMMATRIX PM;
	XMMATRIX VM;

public:

	/**
	* @brief	: Getter for the Projection Matrix.
	* @bug		: No Bugs known.
	**/
	XMMATRIX getPM();

	/**
	* @brief	: Getter for the View Matrix.
	* @bug		: No Bugs known.
	**/
	XMMATRIX getVM();

	/**
	* @brief	: Create the Projection Matrix.
	* @bug		: Can't use it 4 create de PM, have a error from the Lib.
	**/
	void createPM();

	/**
	* @brief	: Create the View Matrix.
	* @bug		: No Bugs known.
	**/
	void createVM();

	/**
	* @brief	: Move the VM.
	* @param	: .
	* @bug		: No Bugs known.
	**/
	void move(XMFLOAT3);
};

