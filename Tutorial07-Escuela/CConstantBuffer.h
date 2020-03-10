/**
* @LC		: 24/02/2020
* @file		: CConstantBuffer.h
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
* @brief	: Class for Constant Buffer.
* @bug		: No Bugs known.
**/
class CConstantBuffer {
public:
	/**
		* @brief	: Constructor.
		* @bug		: No Bugs known.
		**/
	CConstantBuffer();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CConstantBuffer();

	/**
	* @brief	: Init of the class.
	* @param	: DescBuffer.
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
	* @brief	: Returns Buffer Description.
	* @bug		: No Bugs known.
	**/
	D3D11_BUFFER_DESC getBD();
#endif
private:
	DescBuffer ConstantDB;
	CBuffer OrigBuffer;


};

