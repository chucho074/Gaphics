/**
* @LC		: 24/02/2020
* @file		: CUI.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 24/02/2020
* @brief	: A basic description of the what do the doc.
* @bug		: No Bugs known.
**/

/**
* Headers
**/
#include "CUI.h"

CUI::CUI() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	counter = 0;
	CameraState = true;

}

CUI::~CUI() {


}

int CUI::init(UIDesc inDesc) {
	Desc = inDesc;
#ifdef D_DIRECTX
	ImGui_ImplWin32_Init(Desc.hwnd);
	ImGui_ImplDX11_Init(((ID3D11Device*)Desc.Device), ((ID3D11DeviceContext*)Desc.devCont));
#endif 
	ImGui::StyleColorsDark();


	return 0;
}

int CUI::update() {	

	return 0;
}

int CUI::render() {

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	ImGui::Begin("Test");
	ImGui::Text("This is a example");
	if (ImGui::Button("Apuchame")) {
		CameraState = !CameraState;
	}
	
	if (CameraState) {
		ImGui::Text("FP Camera");
	}
	else if (!CameraState) {
		ImGui::Text("God Camera");
	}
	ImGui::Image(Desc.SRV, ImVec2(100,100));
	ImGui::Image(Desc.SRV2, ImVec2(100, 100));
	ImGui::End();
	
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


	return 0;
}

int CUI::destroy() {

	return 0;
}


