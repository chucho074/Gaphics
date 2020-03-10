/**
* @LC		: 24/02/2020
* @file		: CVertexBuffer.h
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
#include "CBuffer.h"


/**
* @brief	: Class for Vertex Buffer.
* @bug		: No Bugs known.
**/
class CVertexBuffer {
public:
	/**
	* @brief	: Initializer.
	* @bug		: No Bugs known.
	**/
	CVertexBuffer();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CVertexBuffer();

	/**
	* @brief	: Init for the class.
	* @bug		: No Bugs known.
	**/
	int init(DescBuffer);

	/**
	* @brief	: Returns the Buffer.
	* @bug		: No Bugs known.
	**/
	void *&getB();

#ifdef D_DIRECTX
	/**
	* @brief	: Returns the Buffer Description.
	* @bug		: No Bugs known.
	**/
	D3D11_BUFFER_DESC getBD();
#endif

private:
	DescBuffer VertexBD;
	CBuffer OrigBuffer;
};