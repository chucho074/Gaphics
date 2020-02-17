/**
* @LC		: 16/02/2020
* @file		: CSamplerState.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
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
struct SamplerDesc {
	D3D11_FILTER Filter;
	D3D11_TEXTURE_ADDRESS_MODE AddressU;
	D3D11_TEXTURE_ADDRESS_MODE AddressV;
	D3D11_TEXTURE_ADDRESS_MODE AddressW;
	FLOAT MipLODBias;
	UINT MaxAnisotropy;
	D3D11_COMPARISON_FUNC ComparisonFunc;
	FLOAT BorderColor[4];
	FLOAT MinLOD;
	FLOAT MaxLOD;
};

/**
* @brief	: Short description of function.
* @param	: Parameter descriptor.
* @bug		: Bug description.
**/
class CSamplerState {
public:
	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	CSamplerState();

	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	~CSamplerState();

	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	int init(SamplerDesc);

	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	ID3D11SamplerState *& getSS();

	/**
	* @brief	: Short description of function.
	* @param	: Parameter descriptor.
	* @bug		: Bug description.
	**/
	D3D11_SAMPLER_DESC getSSDesc();

private:
	ID3D11SamplerState * SamplerLinear;
	D3D11_SAMPLER_DESC Desc;

};

