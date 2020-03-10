/**
* @LC		: 24/02/2020
* @file		: CBuffer.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 07/02/2020
* @brief	: A base class for Buffers.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#pragma once
#include <windows.h>
#ifdef D_DIRECTX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif



/**
* @brief	: Descriptor for Buffers.
* @bug		: No Bugs known.
**/
struct DescBuffer {	
	
	short Usage;
	unsigned int ByteWidth;
	unsigned int BindFlags;
	unsigned int CPUAccessFlags;
	unsigned int MiscFlags;
	unsigned int StructureByteStride;

};



/**
* @brief	: Class for Buffers.
* @bug		: No Bugs knowns.
**/
class CBuffer {
public:
	/**
	* @brief	: Constructor of the class.
	* @bug		: No Bugs known.
	**/
	CBuffer();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CBuffer();

	/**
	* @brief	: Initializer.
	* @bug		: No Bug known.
	**/
	int init();

	/**
	* @brief	: Update data of the descriptor.
	* @bug		: No Bugs known.
	**/
	void updateData();

	/**
	* @brief	: Returns the DX11 Buffer.
	* @bug		: No Bugs known.
	**/
	void *& getBuffer();

	/**
	* @brief	: Set data from other DescBuffer.
	* @param	: DescBuffer.
	* @bug		: No Bugs known.
	**/
	void setDataDesc(DescBuffer);

	/**
	* @brief	: Returns the DX11 Buffer.
	* @bug		: No Bugs known.
	**/
	void *& getDX11Buffer();

#ifdef D_DIRECTX
	/**
	* @brief	: Returns the DX11 Buffer Description.
	* @bug		: No Bugs known.
	**/
	D3D11_BUFFER_DESC getBD();
#endif
private:
#ifdef D_DIRECTX
	D3D11_BUFFER_DESC bd_DX;
#endif
	DescBuffer bd;
	void * PBuffer = NULL;

};