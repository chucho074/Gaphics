/**
* @LC		: 07/02/2020
* @file		: CIndexBuffer.h
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
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
class CIndexBuffer {
public:
	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	CIndexBuffer();

	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	~CIndexBuffer();

	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	int init();

private:

	CBuffer OrigBuffer;



};

