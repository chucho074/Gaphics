/**
* @LC		: 16/02/2020
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
	ZeroMemory(&SamplerLinear, sizeof(SamplerLinear));
	ZeroMemory(&Desc, sizeof(Desc));

	Desc.Filter = inDesc.Filter;
	Desc.AddressU = inDesc.AddressU;
	Desc.AddressV = inDesc.AddressV;
	Desc.AddressW = inDesc.AddressW;
	Desc.ComparisonFunc = inDesc.ComparisonFunc;
	Desc.MinLOD = inDesc.MinLOD;
	Desc.MaxLOD = inDesc.MaxLOD;



	return 0;
}


ID3D11SamplerState *& CSamplerState::getSS() {
	return SamplerLinear;
}


D3D11_SAMPLER_DESC CSamplerState::getSSDesc() {
	return Desc;
}
