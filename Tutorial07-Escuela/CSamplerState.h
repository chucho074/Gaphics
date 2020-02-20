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
* @brief	: Description of the Sampler.
* @bug		: No Bugs known.
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
* @bug		: No Bugs known.
**/
class CSamplerState {
public:
	/**
	* @brief	: Constructor.
	* @bug		: No Bugs known.
	**/
	CSamplerState();

	/**
	* @brief	: Destructor.
	* @bug		: No Bugs known.
	**/
	~CSamplerState();

	/**
	* @brief	: Initializer.
	* @param	: SamplerDesc.
	* @bug		: No Bugs known.
	**/
	int init(SamplerDesc);

	/**
	* @brief	: Getter the SamplerState.
	* @bug		: No Bugs known.
	**/
	ID3D11SamplerState *& getSS();

	/**
	* @brief	: Getter the DX Sampler Desc.
	* @bug		: No Bugs known.
	**/
	D3D11_SAMPLER_DESC getSSDesc();

private:
	ID3D11SamplerState * SamplerLinear = NULL;
	D3D11_SAMPLER_DESC Desc;

};

