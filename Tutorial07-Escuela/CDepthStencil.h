/**
* @LC		: 15/02/2020
* @file		: CDephtStencil.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs
**/

/**
* Headers
**/
#pragma once
#include "CTexture2D.h"

/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
class CDepthStencil {
public:
	CDepthStencil();
	~CDepthStencil();
	int init(TextureDesc);
	ID3D11Texture2D *& getTexture();
	D3D11_TEXTURE2D_DESC getDesc();
private:
	CTexture2D TextureClass;

};

