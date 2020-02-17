/**
* @LC		: 16/02/2020
* @file		: CCamera.h
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


class CRenderTargetView {
public:

	CRenderTargetView();
	~CRenderTargetView();
	ID3D11RenderTargetView *& getRTV();


private:

	ID3D11RenderTargetView* RTV;


};

