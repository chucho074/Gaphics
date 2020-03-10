/**
* @LC		: 24/02/2020
* @file		: CSamplerState.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 15/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/


/**
* Headers
**/
#include "CSamplerState.h"


CSamplerState::CSamplerState() {


}


CSamplerState::~CSamplerState() {


}


int CSamplerState::init(SamplerDesc inDesc) {
#ifdef D_DIRECTX
	ZeroMemory(&SamplerLinear, sizeof(SamplerLinear));
	ZeroMemory(&Desc, sizeof(Desc));
	Desc.Filter = ((D3D11_FILTER)inDesc.Filter);
	Desc.AddressU = ((D3D11_TEXTURE_ADDRESS_MODE)inDesc.AddressU);
	Desc.AddressV = ((D3D11_TEXTURE_ADDRESS_MODE)inDesc.AddressV);
	Desc.AddressW = ((D3D11_TEXTURE_ADDRESS_MODE)inDesc.AddressW);
	Desc.ComparisonFunc = ((D3D11_COMPARISON_FUNC)inDesc.ComparisonFunc);
	Desc.MinLOD = inDesc.MinLOD;
	Desc.MaxLOD = inDesc.MaxLOD;
#endif


	return 0;
}


void *& CSamplerState::getSS() {
	return SamplerLinear;
}

#ifdef D_DIRECTX
D3D11_SAMPLER_DESC CSamplerState::getSSDesc() {
	return Desc;
}
#endif