/**
* @LC		: 24/02/2020
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
#ifdef D_DIRECTX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#endif

enum address {
	ADDRESS_WRAP = 1,
	ADDRESS_MIRROR = 2,
	ADDRESS_CLAMP = 3,
	ADDRESS_BORDER = 4,
	ADDRESS_MIRROR_ONCE = 5
};

enum filter {
	MIN_MAG_MIP_POINT = 0,
	MIN_MAG_POINT_MIP_LINEAR = 0x1,
	MIN_POINT_MAG_LINEAR_MIP_POINT = 0x4,
	MIN_POINT_MAG_MIP_LINEAR = 0x5,
	MIN_LINEAR_MAG_MIP_POINT = 0x10,
	MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x11,
	MIN_MAG_LINEAR_MIP_POINT = 0x14,
	MIN_MAG_MIP_LINEAR = 0x15,
	ANISOTROPIC = 0x55,
	COMPARISON_MIN_MAG_MIP_POINT = 0x80,
	COMPARISON_MIN_MAG_POINT_MIP_LINEAR = 0x81,
	COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT = 0x84,
	COMPARISON_MIN_POINT_MAG_MIP_LINEAR = 0x85,
	COMPARISON_MIN_LINEAR_MAG_MIP_POINT = 0x90,
	COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x91,
	COMPARISON_MIN_MAG_LINEAR_MIP_POINT = 0x94,
	COMPARISON_MIN_MAG_MIP_LINEAR = 0x95,
	COMPARISON_ANISOTROPIC = 0xd5

};

enum comparison {
	COMPARISON_NEVER = 1,
	COMPARISON_LESS = 2,
	COMPARISON_EQUAL = 3,
	COMPARISON_LESS_EQUAL = 4,
	COMPARISON_GREATER = 5,
	COMPARISON_NOT_EQUAL = 6,
	COMPARISON_GREATER_EQUAL = 7,
	COMPARISON_ALWAYS = 8
};

/**
* @brief	: Description of the Sampler.
* @bug		: No Bugs known.
**/
struct SamplerDesc {
	filter Filter;
	address AddressU;
	address AddressV;
	address AddressW;
	float MipLODBias;
	unsigned int MaxAnisotropy;
	comparison ComparisonFunc;
	float BorderColor[4];
	float MinLOD;
	float MaxLOD;
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
	void *& getSS();

#ifdef D_DIRECTX
	/**
	* @brief	: Getter the DX Sampler Desc.
	* @bug		: No Bugs known.
	**/
	D3D11_SAMPLER_DESC getSSDesc();
#endif
private:
	void * SamplerLinear = NULL;
#ifdef D_DIRECTX
	D3D11_SAMPLER_DESC Desc;
#endif
};

