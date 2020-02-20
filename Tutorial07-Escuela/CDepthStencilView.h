/**
* @LC		: 15/02/2020
* @file		: CDepthStencilView.h
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
struct DSViewDesc {
	DXGI_FORMAT Format;
	D3D11_DSV_DIMENSION ViewDimension;
	UINT Flags; 
	union {
		D3D11_TEX1D_DSV Texture1D;
		D3D11_TEX1D_ARRAY_DSV Texture1DArray;
		D3D11_TEX2D_DSV Texture2D;
		D3D11_TEX2D_ARRAY_DSV Texture2DArray;
		D3D11_TEX2DMS_DSV Texture2DMS;
		D3D11_TEX2DMS_ARRAY_DSV Texture2DMSArray;
	};
};

/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
class CDepthStencilView {
public:
	CDepthStencilView();
	~CDepthStencilView();
	int init(DSViewDesc);
	D3D11_DEPTH_STENCIL_VIEW_DESC getDSVDesc();
	ID3D11DepthStencilView *& getDSV();
private:
	ID3D11DepthStencilView * DSV = NULL;
	DSViewDesc Desc;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;


};

