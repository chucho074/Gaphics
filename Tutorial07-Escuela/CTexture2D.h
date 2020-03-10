/**
* @LC		: 24/02/2020
* @file		: CTexture.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 13/02/2020
* @brief	: A basic description of the what do the doc.
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
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
struct TextureDesc {
	UINT Width;
	UINT Height;
	UINT MipLevels;
	UINT ArraySize;
#ifdef D_DIRECTX
	DXGI_FORMAT Format;
	DXGI_SAMPLE_DESC SampleDesc;
	D3D11_USAGE Usage;
#endif
	UINT BindFlags;
	UINT CPUAccessFlags;
	UINT MiscFlags;
};

/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
class CTexture2D {
public:
	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	CTexture2D();
	
	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	~CTexture2D();
	
	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	int init(TextureDesc);

	void *& getDXTexture();

#ifdef D_DIRECTX
	D3D11_TEXTURE2D_DESC getDXDesc();
#endif
private:
	void * Texture;
	TextureDesc Desc;
#ifdef D_DIRECTX
	D3D11_TEXTURE2D_DESC Dx11_Desc;
#endif
};

