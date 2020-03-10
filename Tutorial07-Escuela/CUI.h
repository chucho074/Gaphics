/**
* @LC		: 24/02/2020
* @file		: CUI.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 24/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#pragma once
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_dx11.h"
#include "ImGUI/imgui_impl_win32.h"
#include <windows.h>
#include <iostream>
#include <string>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"

struct UIDesc {
	HWND hwnd;
	void * Device;
	void * devCont;
	void * SRV;
	void * SRV2;
};



class CUI {
public:
	CUI();
	~CUI();
	int init(UIDesc);
	int update();
	int render();
	int destroy();

	bool CameraState;
private:
	int counter;
	UIDesc Desc;

};

