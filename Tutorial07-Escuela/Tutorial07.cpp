//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"

#include <iostream>
#include <string>
#include <vector>


#include "Assimp/Importer.hpp"      // C++ importer interface
#include "Assimp/scene.h"           // Output data structure
#include "Assimp/postprocess.h"     // Post processing flags


#include "stb_image.h"
#include "CCamera.h"
#include "CCameraFP.h"
#include "CDevice.h"
#include "CDeviceContext.h"
#include "CSwapChain.h"
#include "CBuffer.h"
#include "CIndexBuffer.h"
#include "CVertexBuffer.h"
#include "CConstantBuffer.h"
#include "CTexture2D.h"
#include "CDepthStencil.h"
#include "CDepthStencilView.h"
#include "CRenderTarget.h"
#include "CRenderTargetView.h"
#include "CSamplerState.h"
#include "CViewPort.h"
#include "CVertexShader.h"
#include "CPixelShader.h"
#include "CInputLayout.h"
#include "CUI.h"
#include "Mesh.h"



//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
//struct SimpleVertex {
//    vec3 Pos;
//    vec2 Tex;
//};

struct CBNeverChanges {
    mat4x4 mView;
};

struct CBChangeOnResize {
    mat4x4 mProjection;
};

struct CBChangesEveryFrame {
    mat4x4 mWorld;
    XMFLOAT4 vMeshColor;
};


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
#ifdef D_DIRECTX
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11ShaderResourceView*           g_pTextureRV = NULL;
ID3D11ShaderResourceView*           g_pTextureRV_FP = NULL;
mat4x4								g_World;
XMFLOAT4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );
#endif

CCamera Cam;
DescCamera DescCam;
CCameraFP Cam_FP;
DescCameraFP DescCamFP;
CDevice Device;
CSwapChain SC;
CDeviceContext DevContext;
DescBuffer DBuffer;
DescSwapChain DescSC;
CVertexBuffer VBuffer;
CIndexBuffer IBuffer;
CConstantBuffer CBuffer_NC;
CConstantBuffer CBuffer_CoR;
CConstantBuffer CBuffer_CEF;
CConstantBuffer CBuffer_NC_FP;
CConstantBuffer CBuffer_CoR_FP;
CConstantBuffer CBuffer_CEF_FP;
CDepthStencil DepthStencil;
CDepthStencil DepthStencil_FP;
CDepthStencilView DSView;
CDepthStencilView DSView_FP;
CRenderTargetView RTView;
CRenderTargetView RTView_FP;
CSamplerState SS;
CRenderTarget RT;
CRenderTarget RT_FP;
ViewPortDesc VPDesc;
CViewPort VP;
CVertexShader VS;
CPixelShader PS;
CInputLayout IL;
CUI UI;
UIDesc DescUI;




//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK WndProc( HWND, unsigned int, WPARAM, LPARAM );
void Render();
#ifdef D_DIRECTX
HRESULT CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout);
#endif

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

	if (FAILED(InitWindow(hInstance, nCmdShow))) {
		return 0;
	}

    if( FAILED( InitDevice() ) ) {
		//Los destroy
        CleanupDevice();
        return 0;
    }

    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message ) {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else {
			//Los render
            Render();
        }
    }

    CleanupDevice();

    return ( int )msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow ) {

    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_TUTORIAL1 );
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindow( L"TutorialWindowClass", L"Direct3D 11 Tutorial 7", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                           NULL );
	if (!g_hWnd) {
		return E_FAIL;
	}
    ShowWindow( g_hWnd, nCmdShow );

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile( WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut ) {
    HRESULT hr = S_OK;
    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

#ifdef D_DIRECTX

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED(hr) ) {
		if (pErrorBlob != NULL) {
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		}
		if (pErrorBlob) { 
			pErrorBlob->Release(); 
		}
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

#endif
    return S_OK;
}



//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice() {

	Device.init();

	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	unsigned int width = rc.right - rc.left;
	unsigned int height = rc.bottom - rc.top;


#ifdef D_DIRECTX
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	unsigned int numFeatureLevels = ARRAYSIZE(featureLevels);
#endif

	DescSC.BufferCount = 1;
	DescSC.W = width;
	DescSC.H = height;
	DescSC.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	DescSC.numerator = 60;
	DescSC.denominator = 1;
	DescSC.OutputWindow = g_hWnd;
	DescSC.count = 1;
	DescSC.quality = 0;
	DescSC.Windowed = TRUE;

	SC.init(DescSC);


#ifdef D_DIRECTX
	for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, Device.getFlags(), featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &SC.getSC(), &((IDXGISwapChain*&)SC.getSwapC()), &((ID3D11Device*&)Device.getDevice()), &g_featureLevel, (&(ID3D11DeviceContext*&)DevContext.getDContext()));
		if (SUCCEEDED(hr)) {
			break;
		}
	}
#endif
	if (FAILED(hr)) {
		return hr;
	}
#ifdef D_DIRECTX
	hr = ((IDXGISwapChain*&)SC.getSwapC())->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&RT.getBB());
	hr = ((IDXGISwapChain*&)SC.getSwapC())->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&RT_FP.getBB());
#endif
	if (FAILED(hr)) {
		return hr;
	}
	//First render Target View
#ifdef D_DIRECTX
	hr = ((ID3D11Device*&)Device.getDevice())->CreateRenderTargetView(((ID3D11Texture2D*&)RT.getBB()), NULL, &((ID3D11RenderTargetView*&)RTView.getRTV()));
#endif
	//Second Render Target View
	//hr = ((ID3D11Device*&)Device.getDevice())->CreateRenderTargetView(((ID3D11Texture2D*&)RT_FP.getBB()), NULL, &((ID3D11RenderTargetView*&)RTView_FP.getRTV()));

#ifdef D_DIRECTX
	((ID3D11Texture2D*&)RT.getBB())->Release();

	((ID3D11Texture2D*&)RT_FP.getBB())->Release();
#endif
	// Create depth stencil texture
	TextureDesc TextureDesc;


#ifdef D_DIRECTX
	ZeroMemory(&TextureDesc, sizeof(TextureDesc));
	TextureDesc.Width = width;
	TextureDesc.Height = height;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	DepthStencil.init(TextureDesc);
	//DepthStencil_FP.init(TextureDesc);

	hr = ((ID3D11Device*&)Device.getDevice())->CreateTexture2D(&DepthStencil.getDesc(), NULL, &((ID3D11Texture2D*&)DepthStencil.getTexture()));
	//hr = ((ID3D11Device*&)Device.getDevice())->CreateTexture2D(&DepthStencil_FP.getDesc(), NULL, &((ID3D11Texture2D*&)DepthStencil_FP.getTexture()));

#endif
	if (FAILED(hr)) {
		return hr;
	}

	// Create the depth stencil view
	DSViewDesc DescDSV;
#ifdef D_DIRECTX
	DescDSV.Format = ((format)TextureDesc.Format);
	DescDSV.ViewDimension = DIMENSION_TEXTURE2D;
	DescDSV.Texture2D = 0;
	DSView.init(DescDSV);
#endif
#ifdef D_DIRECTX
	//La primera 
	hr = ((ID3D11Device*&)Device.getDevice())->CreateDepthStencilView(((ID3D11Texture2D*&)DepthStencil.getTexture()), &DSView.getDSVDesc(), &((ID3D11DepthStencilView*&)DSView.getDSV()));
	if (FAILED(hr)) {
		return hr;
	}
	//FP
	DSView_FP.init(DescDSV);
	hr = ((ID3D11Device*&)Device.getDevice())->CreateDepthStencilView(((ID3D11Texture2D*&)DepthStencil.getTexture()), &DSView_FP.getDSVDesc(), &((ID3D11DepthStencilView*&)DSView_FP.getDSV()));

#endif
	if (FAILED(hr)) {
		return hr;
	}

#ifdef D_DIRECTX
	((ID3D11DeviceContext*&)DevContext.getDContext())->OMSetRenderTargets(1, &((ID3D11RenderTargetView*&)RTView.getRTV()), ((ID3D11DepthStencilView*&)DSView.getDSV()));

	((ID3D11DeviceContext*&)DevContext.getDContext())->OMSetRenderTargets(1, &((ID3D11RenderTargetView*&)RTView_FP.getRTV()), ((ID3D11DepthStencilView*&)DSView_FP.getDSV()));
#endif

	// Setup the viewport

	VPDesc.Width = width;
	VPDesc.Height = height;
	VPDesc.MinDepth = 0.0f;
	VPDesc.MaxDepth = 1.0f;
	VPDesc.TopLeftX = 0;
	VPDesc.TopLeftY = 0;
	VP.init(VPDesc);

#ifdef D_DIRECTX
	((ID3D11DeviceContext*&)DevContext.getDContext())->RSSetViewports(1, &VP.getDXVP());

	// Compile the vertex shader
	hr = CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0", &((ID3DBlob*&)VS.getVSBlob()));
#endif
	if (FAILED(hr)) {
		MessageBox(NULL, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the vertex shader
#ifdef D_DIRECTX
	hr = ((ID3D11Device*&)Device.getDevice())->CreateVertexShader(((ID3DBlob*&)VS.getVSBlob())->GetBufferPointer(), ((ID3DBlob*&)VS.getVSBlob())->GetBufferSize(), NULL, &((ID3D11VertexShader*&)VS.getVS()));
	if (FAILED(hr)) {
		((ID3DBlob*&)VS.getVSBlob())->Release();
		return hr;
	}
#endif

#ifdef D_DIRECTX
																											//No se porque, pero funciona, whatever
	hr = CreateInputLayoutDescFromVertexShaderSignature(((ID3DBlob*&)VS.getVSBlob()), (ID3D11Device*&)Device.getDevice(), &(ID3D11InputLayout*)IL.getIL());
#endif
	if (FAILED(hr)) {
		return hr;
	}
	// Set the input layout
#ifdef D_DIRECTX
	((ID3D11DeviceContext*&)DevContext.getDContext())->IASetInputLayout(((ID3D11InputLayout*&)IL.getIL()));


	// Compile the pixel shader
	hr = CompileShaderFromFile(L"Tutorial07.fx", "PS", "ps_4_0", &((ID3DBlob*&)PS.getPSBlob()));
	if (FAILED(hr)) {
		MessageBox(NULL, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create the pixel shader
	hr = ((ID3D11Device*&)Device.getDevice())->CreatePixelShader(((ID3DBlob*&)PS.getPSBlob())->GetBufferPointer(), ((ID3DBlob*&)PS.getPSBlob())->GetBufferSize(), NULL, &((ID3D11PixelShader*&)PS.getPS()));
	((ID3DBlob*&)PS.getPSBlob())->Release();
	if (FAILED(hr)) {
		return hr;
	}
#endif
	// Create vertex buffer
	SimpleVertex vertices[] = {
		{ vec3(-1.0f, 1.0f, -1.0f),	vec2(0.0f, 0.0f) },
		{ vec3(1.0f, 1.0f, -1.0f),	vec2(1.0f, 0.0f) },
		{ vec3(1.0f, 1.0f, 1.0f),		vec2(1.0f, 1.0f) },
		{ vec3(-1.0f, 1.0f, 1.0f),	vec2(0.0f, 1.0f) },

		{ vec3(-1.0f, -1.0f, -1.0f),	vec2(0.0f, 0.0f) },
		{ vec3(1.0f, -1.0f, -1.0f),	vec2(1.0f, 0.0f) },
		{ vec3(1.0f, -1.0f, 1.0f),	vec2(1.0f, 1.0f) },
		{ vec3(-1.0f, -1.0f, 1.0f),	vec2(0.0f, 1.0f) },

		{ vec3(-1.0f, -1.0f, 1.0f),	vec2(0.0f, 0.0f) },
		{ vec3(-1.0f, -1.0f, -1.0f),	vec2(1.0f, 0.0f) },
		{ vec3(-1.0f, 1.0f, -1.0f),	vec2(1.0f, 1.0f) },
		{ vec3(-1.0f, 1.0f, 1.0f),	vec2(0.0f, 1.0f) },

		{ vec3(1.0f, -1.0f, 1.0f),	vec2(0.0f, 0.0f) },
		{ vec3(1.0f, -1.0f, -1.0f),	vec2(1.0f, 0.0f) },
		{ vec3(1.0f, 1.0f, -1.0f),	vec2(1.0f, 1.0f) },
		{ vec3(1.0f, 1.0f, 1.0f),		vec2(0.0f, 1.0f) },

		{ vec3(-1.0f, -1.0f, -1.0f),	vec2(0.0f, 0.0f) },
		{ vec3(1.0f, -1.0f, -1.0f),	vec2(1.0f, 0.0f) },
		{ vec3(1.0f, 1.0f, -1.0f),	vec2(1.0f, 1.0f) },
		{ vec3(-1.0f, 1.0f, -1.0f),	vec2(0.0f, 1.0f) },

		{ vec3(-1.0f, -1.0f, 1.0f),	vec2(0.0f, 0.0f) },
		{ vec3(1.0f, -1.0f, 1.0f),	vec2(1.0f, 0.0f) },
		{ vec3(1.0f, 1.0f, 1.0f),		vec2(1.0f, 1.0f) },
		{ vec3(-1.0f, 1.0f, 1.0f),	vec2(0.0f, 1.0f) },
	};


	ZeroMemory(&DBuffer, sizeof(DBuffer));
	DBuffer.Usage = D3D11_USAGE_DEFAULT;
	DBuffer.CPUAccessFlags = 0;

	DBuffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	DBuffer.ByteWidth = sizeof(SimpleVertex) * 24;
	VBuffer.init(DBuffer);

#ifdef D_DIRECTX
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = ((ID3D11Device*&)Device.getDevice())->CreateBuffer(&VBuffer.getBD(), &InitData, &((ID3D11Buffer*&)VBuffer.getB()));
#endif
	if (FAILED(hr)) {
		return hr;
	}
	// Set vertex buffer
	unsigned int stride = sizeof(SimpleVertex);
	unsigned int offset = 0;
#ifdef D_DIRECTX
	((ID3D11DeviceContext*&)DevContext.getDContext())->IASetVertexBuffers(0, 1, &((ID3D11Buffer*&)VBuffer.getB()), &stride, &offset);
#endif
	//std::vector<Mesh> meshes;


	// Create index buffer
	WORD indices[] = {
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

#ifdef D_DIRECTX
	DBuffer.ByteWidth = sizeof(WORD) * 36;
	DBuffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IBuffer.init(DBuffer);
	InitData.pSysMem = indices;
	hr = ((ID3D11Device*&)Device.getDevice())->CreateBuffer(&IBuffer.getBD(), &InitData, &((ID3D11Buffer*&)IBuffer.getB()));
#endif
	if (FAILED(hr)) {
		return hr;
	}
#ifdef D_DIRECTX
	// Set index buffer
	((ID3D11DeviceContext*&)DevContext.getDContext())->IASetIndexBuffer(((ID3D11Buffer*&)IBuffer.getB()), DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	((ID3D11DeviceContext*&)DevContext.getDContext())->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffers	
	DBuffer.ByteWidth = sizeof(CBNeverChanges);
	DBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CBuffer_NC.init(DBuffer);
	hr = ((ID3D11Device*&)Device.getDevice())->CreateBuffer(&CBuffer_NC.getBD(), NULL, &((ID3D11Buffer*&)CBuffer_NC.getB()));
	if (FAILED(hr)) {
		return hr;
	}
	CBuffer_NC_FP.init(DBuffer);
	hr = ((ID3D11Device*&)Device.getDevice())->CreateBuffer(&CBuffer_NC_FP.getBD(), NULL, &((ID3D11Buffer*&)CBuffer_NC_FP.getB()));
	if (FAILED(hr)) {
		return hr;
	}
	DBuffer.ByteWidth = sizeof(CBChangeOnResize);
	CBuffer_CoR.init(DBuffer);
	hr = ((ID3D11Device*&)Device.getDevice())->CreateBuffer(&CBuffer_CoR.getBD(), NULL, &((ID3D11Buffer*&)CBuffer_CoR.getB()));
	if (FAILED(hr)) {
		return hr;
	}
	CBuffer_CoR_FP.init(DBuffer);
	hr = ((ID3D11Device*&)Device.getDevice())->CreateBuffer(&CBuffer_CoR_FP.getBD(), NULL, &((ID3D11Buffer*&)CBuffer_CoR_FP.getB()));

	if (FAILED(hr)) {
		return hr;
	}

	//ChangeEveryFrame
	DBuffer.ByteWidth = sizeof(CBChangesEveryFrame);
	CBuffer_CEF.init(DBuffer);
    hr = ((ID3D11Device*&)Device.getDevice())->CreateBuffer( &CBuffer_CEF.getBD(), NULL, &((ID3D11Buffer*&)CBuffer_CEF.getB()));
	if (FAILED(hr)) {
		return hr;
	}
	CBuffer_CEF_FP.init(DBuffer);
	hr = ((ID3D11Device*&)Device.getDevice())->CreateBuffer(&CBuffer_CEF_FP.getBD(), NULL, &((ID3D11Buffer*&)CBuffer_CEF_FP.getB()));
	if (FAILED(hr)) {
		return hr;
	}
    // Load the Texture
    hr = D3DX11CreateShaderResourceViewFromFile((ID3D11Device*&)Device.getDevice(), L"seafloor.dds", NULL, NULL, &g_pTextureRV, NULL );
	
	if (FAILED(hr)) {
		return hr;
	}
#endif

    // Create the sample state
	SamplerDesc sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
    sampDesc.Filter =			MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU =			ADDRESS_WRAP;
    sampDesc.AddressV =			ADDRESS_WRAP;
    sampDesc.AddressW =			ADDRESS_WRAP;
    sampDesc.ComparisonFunc =	COMPARISON_NEVER;
    sampDesc.MinLOD =			0;
    sampDesc.MaxLOD =			D3D11_FLOAT32_MAX;

	SS.init(sampDesc);
#ifdef D_DIRECTX
    hr = ((ID3D11Device*&)Device.getDevice())->CreateSamplerState( &SS.getSSDesc(), &((ID3D11SamplerState*&)SS.getSS()) );
#endif
	if (FAILED(hr)) {
		return hr;
	}
    // Initialize the world matrices
#ifdef D_DIRECTX
	g_World = mat4x4(1);
#endif
	DescCam.W = (rc.right - rc.left);
	DescCam.H = (rc.bottom - rc.top);
	DescCam.Fov = XM_PIDIV4;
	DescCam.Near = 0.01f;
	DescCam.Far = 100.f;
	Cam.init(DescCam);

	DescCamFP.W = (rc.right - rc.left);
	DescCamFP.H = (rc.bottom - rc.top);
	DescCamFP.Fov = XM_PIDIV4;
	DescCamFP.Near = 0.01f;
	DescCamFP.Far = 100.f;
	Cam_FP.init(DescCamFP);

	//First
    CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = Cam.getVM();
#ifdef D_DIRECTX
	((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_NC.getB()), 0, NULL, &cbNeverChanges, 0, 0 );
	
#endif

	//Second
	CBNeverChanges cbNeverChanges_FP;
	cbNeverChanges_FP.mView = Cam_FP.getVM();
#ifdef D_DIRECTX
	((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_NC_FP.getB()), 0, NULL, &cbNeverChanges_FP, 0, 0);

#endif

	//First
	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.mProjection = transpose(Cam.getPM());
#ifdef D_DIRECTX
	((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_CoR.getB()), 0, NULL, &cbChangesOnResize, 0, 0);
#endif

    // Second
	CBChangeOnResize cbChangesOnResize_FP;
	cbChangesOnResize_FP.mProjection = transpose(Cam_FP.getPM());
#ifdef D_DIRECTX	
	((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_CoR_FP.getB()), 0, NULL, &cbChangesOnResize_FP, 0, 0);

#endif

	D3D11_TEXTURE2D_DESC X;
	ZeroMemory(&X, sizeof(X));
	X.Width = width;
	X.Height = height;
	X.MipLevels = X.ArraySize = 1;
	X.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	X.SampleDesc.Count = 1;
	X.Usage = D3D11_USAGE_DEFAULT;
	X.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	X.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	X.MiscFlags = 0;
#ifdef D_DIRECTX
	hr = ((ID3D11Device*&)Device.getDevice())->CreateTexture2D(&X, NULL, &((ID3D11Texture2D*&)RT_FP.getBB()));
#endif
	if (FAILED(hr)) {
		return hr;
	}
#ifdef D_DIRECTX
	D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
	rtDesc.Format = X.Format;
	rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtDesc.Texture2D.MipSlice = 0;

	hr = ((ID3D11Device*&)Device.getDevice())->CreateRenderTargetView(((ID3D11Texture2D*&)RT_FP.getBB()), &rtDesc, &((ID3D11RenderTargetView*&)RTView_FP.getRTV()));

	D3D11_SHADER_RESOURCE_VIEW_DESC view;
	view.Format = X.Format;
	view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	view.Texture2D.MostDetailedMip = 0;
	view.Texture2D.MipLevels = 1;

	hr = ((ID3D11Device*&)Device.getDevice())->CreateShaderResourceView(((ID3D11Texture2D*&)RT_FP.getBB()), &view, &g_pTextureRV_FP);
#endif
	if (FAILED(hr)) {
		return hr;
	}


	UIDesc DescUI;
	DescUI.Device = Device.getDevice();
	DescUI.devCont = DevContext.getDContext();
	DescUI.hwnd = g_hWnd;
#ifdef D_DIRECTX
	DescUI.SRV = g_pTextureRV;
	DescUI.SRV2 = g_pTextureRV_FP;
#endif
	UI.init(DescUI);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice() {
#ifdef D_DIRECTX
	if (((ID3D11DeviceContext*&)DevContext.getDContext()))		{ ((ID3D11DeviceContext*&)DevContext.getDContext())->ClearState(); }
	if (((ID3D11SamplerState*&)SS.getSS()))						{ ((ID3D11SamplerState*&)SS.getSS())->Release(); }
	if (g_pTextureRV)					{ g_pTextureRV->Release(); }
	if (g_pTextureRV_FP) { g_pTextureRV_FP->Release(); }
	if (((ID3D11Buffer*&)CBuffer_NC.getB()))				{ ((ID3D11Buffer*&)CBuffer_NC.getB())->Release(); }
	if (((ID3D11Buffer*&)CBuffer_NC_FP.getB()))				{ ((ID3D11Buffer*&)CBuffer_NC_FP.getB())->Release(); }
	if (((ID3D11Buffer*&)CBuffer_CoR.getB()))				{ ((ID3D11Buffer*&)CBuffer_CoR.getB())->Release(); }
	if (((ID3D11Buffer*&)CBuffer_CoR_FP.getB()))				{ ((ID3D11Buffer*&)CBuffer_CoR_FP.getB())->Release(); }
	if (((ID3D11Buffer*&)CBuffer_CEF.getB()))				{ ((ID3D11Buffer*&)CBuffer_CEF.getB())->Release(); }
	if (((ID3D11Buffer*&)CBuffer_CEF_FP.getB())) { ((ID3D11Buffer*&)CBuffer_CEF_FP.getB())->Release(); }
	if (((ID3D11Buffer*&)VBuffer.getB()))					{ ((ID3D11Buffer*&)VBuffer.getB())->Release(); }
	if (((ID3D11Buffer*&)IBuffer.getB()))					{ ((ID3D11Buffer*&)IBuffer.getB())->Release(); }
	if (((ID3D11InputLayout*&)IL.getIL()))						{ ((ID3D11InputLayout*&)IL.getIL())->Release(); }
	if (((ID3D11VertexShader*&)VS.getVS()))						{ ((ID3D11VertexShader*&)VS.getVS())->Release(); }
	if (((ID3D11PixelShader*&)PS.getPS()))						{ ((ID3D11PixelShader*&)PS.getPS())->Release(); }
	if (((ID3D11Texture2D*&)DepthStencil.getTexture()))		{ ((ID3D11Texture2D*&)DepthStencil.getTexture())->Release(); }
	//if (((ID3D11Texture2D*&)DepthStencil_FP.getTexture())) { ((ID3D11Texture2D*&)DepthStencil_FP.getTexture())->Release(); }
	if (((ID3D11DepthStencilView*&)DSView.getDSV()))				{ ((ID3D11DepthStencilView*&)DSView.getDSV())->Release(); }
	if (((ID3D11DepthStencilView*&)DSView_FP.getDSV())) { ((ID3D11DepthStencilView*&)DSView_FP.getDSV())->Release(); }
	if (((ID3D11RenderTargetView*&)RTView.getRTV()))				{ ((ID3D11RenderTargetView*&)RTView.getRTV())->Release(); }
	if (((ID3D11RenderTargetView*&)RTView_FP.getRTV()))				{ ((ID3D11RenderTargetView*&)RTView_FP.getRTV())->Release(); }
	if (((IDXGISwapChain*&)SC.getSwapC()))					{ ((IDXGISwapChain*&)SC.getSwapC())->Release(); }
	if (((ID3D11DeviceContext*&)DevContext.getDContext()))		{ ((ID3D11DeviceContext*&)DevContext.getDContext())->Release(); }
	if (((ID3D11Device*&)Device.getDevice()))				{ ((ID3D11Device*&)Device.getDevice())->Release(); }
#endif
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam ) {
    PAINTSTRUCT ps;
    HDC hdc;

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) {
		return true;
	}
	switch (message) {
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	#ifdef D_DIRECTX 
	case WM_SIZING: {
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		unsigned int width = rc.right - rc.left;
		unsigned int height = rc.bottom - rc.top;
		Cam.updateSize(width,  height);
		Cam.updatePM();

		CBChangeOnResize cbChangesOnResize;
		cbChangesOnResize.mProjection = transpose(Cam.getPM());
		((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_CoR.getB()), 0, NULL, &cbChangesOnResize, 0, 0); 
		
		Cam_FP.updateSize(width, height);
		Cam_FP.updatePM();
		CBChangeOnResize cbChangesOnResize_FP;
		cbChangesOnResize_FP.mProjection = transpose(Cam_FP.getPM());
		((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_CoR_FP.getB()), 0, NULL, &cbChangesOnResize_FP, 0, 0);
		break;
	}
	#endif
	#ifdef D_DIRECTX
	case WM_SIZE: {
		if (DevContext.getDContext() != nullptr) {
			RECT rc;
			GetClientRect(g_hWnd, &rc);
			unsigned int width = rc.right - rc.left;
			unsigned int height = rc.bottom - rc.top;
			Cam.updateSize(width, height);
			Cam.updatePM();

			CBChangeOnResize cbChangesOnResize;
			cbChangesOnResize.mProjection = transpose(Cam.getPM());
			((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_CoR.getB()), 0, NULL, &cbChangesOnResize, 0, 0);
			
			
			g_World = mat4(1.0f);
			if (((IDXGISwapChain*&)SC.getSwapC())) {
				((ID3D11DeviceContext*&)DevContext.getDContext())->OMSetRenderTargets(0, 0, 0);
				((ID3D11RenderTargetView*&)RTView.getRTV())->Release();
				
				HRESULT hr;
				hr = ((IDXGISwapChain*&)SC.getSwapC())->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

				CBuffer Buffer_Temp;
				hr = ((IDXGISwapChain*&)SC.getSwapC())->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&Buffer_Temp.getBuffer());
				hr = ((ID3D11Device*&)Device.getDevice())->CreateRenderTargetView(((ID3D11Buffer*)Buffer_Temp.getBuffer()), NULL, &((ID3D11RenderTargetView*&)RTView.getRTV()));
				((ID3D11Buffer*)Buffer_Temp.getBuffer())->Release();

				((ID3D11Texture2D*&)DepthStencil.getTexture())->Release();
				
				TextureDesc TextureDesc;

				ZeroMemory(&TextureDesc, sizeof(TextureDesc));
				TextureDesc.Width = width;
				TextureDesc.Height = height;
				TextureDesc.MipLevels = 1;
				TextureDesc.ArraySize = 1;
				TextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				TextureDesc.SampleDesc.Count = 1;
				TextureDesc.SampleDesc.Quality = 0;
				TextureDesc.Usage = D3D11_USAGE_DEFAULT;
				TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				TextureDesc.CPUAccessFlags = 0;
				TextureDesc.MiscFlags = 0;

				DepthStencil.init(TextureDesc);

				
				hr = ((ID3D11Device*&)Device.getDevice())->CreateTexture2D(&DepthStencil.getDesc(), NULL, &((ID3D11Texture2D*&)DepthStencil.getTexture()));
				
				DSViewDesc DescDSV;

				DescDSV.Format = (format)TextureDesc.Format;
				DescDSV.ViewDimension = DIMENSION_TEXTURE2D;
				DescDSV.Texture2D = 0;

				((ID3D11DepthStencilView*&)DSView.getDSV())->Release();
				
				DSView.init(DescDSV);
				DSView_FP.init(DescDSV);


				hr = ((ID3D11Device*&)Device.getDevice())->CreateDepthStencilView(((ID3D11Texture2D*&)DepthStencil.getTexture()), &DSView.getDSVDesc(), &((ID3D11DepthStencilView*&)DSView.getDSV()));
				((ID3D11DeviceContext*&)DevContext.getDContext())->OMSetRenderTargets(1, &((ID3D11RenderTargetView*&)RTView.getRTV()), ((ID3D11DepthStencilView*&)DSView.getDSV()));

				//Segundo Render Target
				
				((ID3D11RenderTargetView*&)RTView_FP.getRTV())->Release();

				D3D11_TEXTURE2D_DESC X;
				ZeroMemory(&X, sizeof(X));
				X.Width = width;
				X.Height = height;
				X.MipLevels = X.ArraySize = 1;
				X.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				X.SampleDesc.Count = 1;
				X.Usage = D3D11_USAGE_DEFAULT;
				X.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
				X.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				X.MiscFlags = 0;

				hr = ((ID3D11Device*&)Device.getDevice())->CreateTexture2D(&X, NULL, &((ID3D11Texture2D*&)RT_FP.getBB()));

				if (FAILED(hr)) {
					return hr;
				}

				D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
				rtDesc.Format = X.Format;
				rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
				rtDesc.Texture2D.MipSlice = 0;

				

				hr = ((ID3D11Device*&)Device.getDevice())->CreateRenderTargetView(((ID3D11Texture2D*&)RT_FP.getBB()), &rtDesc, &((ID3D11RenderTargetView*&)RTView_FP.getRTV()));

				D3D11_SHADER_RESOURCE_VIEW_DESC view;
				view.Format = X.Format;
				view.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				view.Texture2D.MostDetailedMip = 0;
				view.Texture2D.MipLevels = 1;

				hr = ((ID3D11Device*&)Device.getDevice())->CreateShaderResourceView(((ID3D11Texture2D*&)RT_FP.getBB()), &view, &g_pTextureRV_FP);
				if (FAILED(hr)) {
					return hr;
				}
				
				hr = ((ID3D11Device*&)Device.getDevice())->CreateDepthStencilView(((ID3D11Texture2D*&)DepthStencil.getTexture()), &DSView_FP.getDSVDesc(), &((ID3D11DepthStencilView*&)DSView_FP.getDSV()));

				((ID3D11DeviceContext*&)DevContext.getDContext())->OMSetRenderTargets(1, &((ID3D11RenderTargetView*&)RTView_FP.getRTV()), ((ID3D11DepthStencilView*&)DSView_FP.getDSV()));
				

				VPDesc.Width = width;
				VPDesc.Height = height;
				VPDesc.MinDepth = 0.0f;
				VPDesc.MaxDepth = 1.0f;
				VPDesc.TopLeftX = 0;
				VPDesc.TopLeftY = 0;
				CViewPort ViewPort_Temp;
				ViewPort_Temp.init(VPDesc);

				((ID3D11DeviceContext*&)DevContext.getDContext())->RSSetViewports(1, &ViewPort_Temp.getDXVP());
			}

			Cam_FP.updateSize(width, height);
			Cam_FP.updatePM();

			CBChangeOnResize cbChangesOnResize_FP;
			cbChangesOnResize_FP.mProjection = transpose(Cam_FP.getPM());
			((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_CoR_FP.getB()), 0, NULL, &cbChangesOnResize_FP, 0, 0);


		}
		break;

	}
	#endif
	#ifdef D_DIRECTX
	case WM_KEYDOWN: {
		if (UI.CameraState == true) {
			if ((wParam == VK_UP) || (wParam == 'W' || wParam == 'w')) {
				vec3 moving = { 0.f, 0.f, 0.1f };
				Cam.move(moving);
			}
			else if ((wParam == VK_DOWN) || (wParam == 'S' || wParam == 's')) {
				vec3 moving = { 0.f, 0.f, -0.1f };
				Cam.move(moving);
			}
			if ((wParam == VK_LEFT) || (wParam == 'A' || wParam == 'a')) {
				vec3 moving = { -0.1f, 0.f, 0.f };
				Cam.move(moving);
			}
			else if ((wParam == VK_RIGHT) || (wParam == 'D' || wParam == 'd')) {
				vec3 moving = { 0.1f, 0.f, 0.f };
				Cam.move(moving);
			}
			if (wParam == 'E' || wParam == 'e') {
				vec3 moving = { 0.f, 0.1f, 0.f };
				Cam.move(moving);
			}
			else if (wParam == 'Q' || wParam == 'q') {
				vec3 moving = { 0.f, -0.1f, 0.f };
				Cam.move(moving);
			}
			CBNeverChanges cbNeverChanges;
			cbNeverChanges.mView = Cam.getVM();

			((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_NC.getB()), 0, NULL, &cbNeverChanges, 0, 0);
		}
		else if (UI.CameraState == false) {
			if ((wParam == VK_UP) || (wParam == 'W' || wParam == 'w')) {
				vec3 moving = { 0.f, 0.f, 0.1f };
				Cam_FP.move(moving);
			}
			else if ((wParam == VK_DOWN) || (wParam == 'S' || wParam == 's')) {
				vec3 moving = { 0.f, 0.f, -0.1f };
				Cam_FP.move(moving);
			}
			if ((wParam == VK_LEFT) || (wParam == 'A' || wParam == 'a')) {
				vec3 moving = { -0.1f, 0.f, 0.f };
				Cam_FP.move(moving);
			}
			else if ((wParam == VK_RIGHT) || (wParam == 'D' || wParam == 'd')) {
				vec3 moving = { 0.1f, 0.f, 0.f };
				Cam_FP.move(moving);
			}
			if (wParam == 'E' || wParam == 'e') {
				vec3 moving = { 0.f, 0.1f, 0.f };
				Cam_FP.move(moving);
			}
			else if (wParam == 'Q' || wParam == 'q') {
				vec3 moving = { 0.f, -0.1f, 0.f };
				Cam_FP.move(moving);
			}
			CBNeverChanges cbNeverChanges2;
			cbNeverChanges2.mView = Cam_FP.getVM();
			((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_NC_FP.getB()), 0, NULL, &cbNeverChanges2, 0, 0);
		}
		break;
	}
	#endif
	case WM_RBUTTONDOWN: {
		if (UI.CameraState == true) {
			POINT mouse;
			GetCursorPos(&mouse);
			Cam.initPos = { mouse.x, mouse.y, 0.f };
			Cam.mouseClicked = true;
		}
		else if (UI.CameraState == false) {
			POINT mouse;
			GetCursorPos(&mouse);
			Cam_FP.initPos = { mouse.x, mouse.y, 0.f };
			Cam_FP.mouseClicked = true;
		}
		break;
	}
#ifdef D_DIRECTX
	case WM_MOUSEMOVE: {
		if (UI.CameraState == true) {
			if (Cam.mouseClicked) {
				POINT endPoint;
				GetCursorPos(&endPoint);
				Cam.endPos = { endPoint.x, endPoint.y, 0.f };
				SetCursorPos((int)Cam.initPos.x, (int)Cam.initPos.y);
				Cam.dir = Cam.initPos - Cam.endPos;
				Cam.rotate(Cam.dir);

				CBNeverChanges cbNeverChanges;
				cbNeverChanges.mView = Cam.getVM();
				((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_NC.getB()), 0, NULL, &cbNeverChanges, 0, 0);

			}
		}
		else if (UI.CameraState == false) {
			if (Cam_FP.mouseClicked) {
				POINT endPoint;
				GetCursorPos(&endPoint);
				Cam_FP.endPos = { endPoint.x, endPoint.y, 0.f };
				SetCursorPos((int)Cam_FP.initPos.x, (int)Cam_FP.initPos.y);
				Cam_FP.dir = Cam_FP.initPos - Cam_FP.endPos;
				Cam_FP.rotate(Cam_FP.dir);

				CBNeverChanges cbNeverChanges;
				cbNeverChanges.mView = Cam_FP.getVM();
				((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_NC_FP.getB()), 0, NULL, &cbNeverChanges, 0, 0);
			}
		}
			break;
	}
#endif
	case WM_RBUTTONUP: {
		if (UI.CameraState == true) {
			Cam.mouseClicked = false;
		}
		else if (UI.CameraState == false) {
			Cam_FP.mouseClicked = false;
		}
		break;
	}
	default: {
		return DefWindowProc(hWnd, message, wParam, lParam);
	 }
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render() {
#ifdef D_DIRECTX
    // Update our time
    static float t = 0.0f;
    if( g_driverType == D3D_DRIVER_TYPE_REFERENCE ) {
        t += ( float )XM_PI * 0.0125f;
    }
    else {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();
        if( dwTimeStart == 0 )
            dwTimeStart = dwTimeCur;
        t = ( dwTimeCur - dwTimeStart ) / 1000.0f;
    }

    // Rotate cube around the origin
    //g_World = XMMatrixRotationY( t );

    // Modify the color
    g_vMeshColor.x = ( sinf( t * 1.0f ) + 1.0f ) * 0.5f;
    g_vMeshColor.y = ( cosf( t * 3.0f ) + 1.0f ) * 0.5f;
    g_vMeshColor.z = ( sinf( t * 5.0f ) + 1.0f ) * 0.5f;

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha

	if (UI.CameraState == true) {
		
		((ID3D11DeviceContext*&)DevContext.getDContext())->OMSetRenderTargets(1, &((ID3D11RenderTargetView*&)RTView_FP.getRTV()), ((ID3D11DepthStencilView*&)DSView_FP.getDSV()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->ClearRenderTargetView(((ID3D11RenderTargetView*&)RTView_FP.getRTV()), ClearColor);

		//
		// Clear the depth buffer to 1.0 (max depth)
		//
		((ID3D11DeviceContext*&)DevContext.getDContext())->ClearDepthStencilView(((ID3D11DepthStencilView*&)DSView_FP.getDSV()), D3D11_CLEAR_DEPTH, 1.0f, 0);


		//
		// Update variables that change once per frame
		//

		//La primera
		g_World = glm::mat4(1.f);
		CBChangesEveryFrame cb;
		cb.mWorld = transpose(g_World);
		cb.vMeshColor = g_vMeshColor;
		((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_CEF_FP.getB()), 0, NULL, &cb, 0, 0);

		//
		// Render the cube
		//
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetShader(((ID3D11VertexShader*&)VS.getVS()), NULL, 0);
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(0, 1, &((ID3D11Buffer*&)CBuffer_NC_FP.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(1, 1, &((ID3D11Buffer*&)CBuffer_CoR_FP.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(2, 1, &((ID3D11Buffer*&)CBuffer_CEF_FP.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShader(((ID3D11PixelShader*&)PS.getPS()), NULL, 0);
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetConstantBuffers(2, 1, &((ID3D11Buffer*&)CBuffer_CEF_FP.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShaderResources(0, 1, &g_pTextureRV);
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetSamplers(0, 1, &((ID3D11SamplerState*&)SS.getSS()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->DrawIndexed(36, 0, 0);
		ID3D11ShaderResourceView* temp = NULL;
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShaderResources(0, 1, &temp);

		((ID3D11DeviceContext*&)DevContext.getDContext())->OMSetRenderTargets(1, &((ID3D11RenderTargetView*&)RTView.getRTV()), ((ID3D11DepthStencilView*&)DSView.getDSV()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->ClearRenderTargetView(((ID3D11RenderTargetView*&)RTView.getRTV()), ClearColor);
		((ID3D11DeviceContext*&)DevContext.getDContext())->ClearDepthStencilView(((ID3D11DepthStencilView*&)DSView.getDSV()), D3D11_CLEAR_DEPTH, 1.0f, 0);


		//La otra
		g_World = glm::mat4(1.f);
		CBChangesEveryFrame cb2;
		cb2.mWorld = transpose(g_World);
		cb2.vMeshColor = g_vMeshColor;
		((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_CEF.getB()), 0, NULL, &cb2, 0, 0);

		//
		// Render the cube
		//
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetShader(((ID3D11VertexShader*&)VS.getVS()), NULL, 0);
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(0, 1, &((ID3D11Buffer*&)CBuffer_NC.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(1, 1, &((ID3D11Buffer*&)CBuffer_CoR.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(2, 1, &((ID3D11Buffer*&)CBuffer_CEF.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShader(((ID3D11PixelShader*&)PS.getPS()), NULL, 0);
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetConstantBuffers(2, 1, &((ID3D11Buffer*&)CBuffer_CEF.getB()));

		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShaderResources(0, 1, &g_pTextureRV_FP);
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetSamplers(0, 1, &((ID3D11SamplerState*&)SS.getSS()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->DrawIndexed(36, 0, 0);
		ID3D11ShaderResourceView* temp2 = NULL;
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShaderResources(0, 1, &temp2);
		UI.render();
	}
	else if (UI.CameraState == false) {
		
		((ID3D11DeviceContext*&)DevContext.getDContext())->OMSetRenderTargets(1, &((ID3D11RenderTargetView*&)RTView.getRTV()), ((ID3D11DepthStencilView*&)DSView.getDSV()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->ClearRenderTargetView(((ID3D11RenderTargetView*&)RTView.getRTV()), ClearColor);

		//
		// Clear the depth buffer to 1.0 (max depth)
		//
		((ID3D11DeviceContext*&)DevContext.getDContext())->ClearDepthStencilView(((ID3D11DepthStencilView*&)DSView_FP.getDSV()), D3D11_CLEAR_DEPTH, 1.0f, 0);


		//La otra
		g_World = glm::mat4(1.f);
		CBChangesEveryFrame cb2;
		cb2.mWorld = transpose(g_World);
		cb2.vMeshColor = g_vMeshColor;
		((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_CEF.getB()), 0, NULL, &cb2, 0, 0);

		//
		// Render the cube
		//
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetShader(((ID3D11VertexShader*&)VS.getVS()), NULL, 0);
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(0, 1, &((ID3D11Buffer*&)CBuffer_NC.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(1, 1, &((ID3D11Buffer*&)CBuffer_CoR.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(2, 1, &((ID3D11Buffer*&)CBuffer_CEF.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShader(((ID3D11PixelShader*&)PS.getPS()), NULL, 0);
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetConstantBuffers(2, 1, &((ID3D11Buffer*&)CBuffer_CEF.getB()));

		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShaderResources(0, 1, &g_pTextureRV_FP);
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetSamplers(0, 1, &((ID3D11SamplerState*&)SS.getSS()));
		
		ID3D11ShaderResourceView* temp2 = NULL;
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShaderResources(0, 1, &temp2);
		UI.render();

		//La primera
		g_World = glm::mat4(1.f);
		CBChangesEveryFrame cb;
		cb.mWorld = transpose(g_World);
		cb.vMeshColor = g_vMeshColor;
		((ID3D11DeviceContext*&)DevContext.getDContext())->UpdateSubresource(((ID3D11Buffer*&)CBuffer_CEF_FP.getB()), 0, NULL, &cb, 0, 0);

		//
		// Render the cube
		//
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetShader(((ID3D11VertexShader*&)VS.getVS()), NULL, 0);
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(0, 1, &((ID3D11Buffer*&)CBuffer_NC_FP.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(1, 1, &((ID3D11Buffer*&)CBuffer_CoR_FP.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->VSSetConstantBuffers(2, 1, &((ID3D11Buffer*&)CBuffer_CEF_FP.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShader(((ID3D11PixelShader*&)PS.getPS()), NULL, 0);
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetConstantBuffers(2, 1, &((ID3D11Buffer*&)CBuffer_CEF_FP.getB()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShaderResources(0, 1, &g_pTextureRV_FP);
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetSamplers(0, 1, &((ID3D11SamplerState*&)SS.getSS()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->DrawIndexed(36, 0, 0);
		ID3D11ShaderResourceView* temp = NULL;
		((ID3D11DeviceContext*&)DevContext.getDContext())->PSSetShaderResources(0, 1, &temp);

		((ID3D11DeviceContext*&)DevContext.getDContext())->OMSetRenderTargets(1, &((ID3D11RenderTargetView*&)RTView_FP.getRTV()), ((ID3D11DepthStencilView*&)DSView.getDSV()));
		((ID3D11DeviceContext*&)DevContext.getDContext())->ClearRenderTargetView(((ID3D11RenderTargetView*&)RTView_FP.getRTV()), ClearColor);
		((ID3D11DeviceContext*&)DevContext.getDContext())->ClearDepthStencilView(((ID3D11DepthStencilView*&)DSView.getDSV()), D3D11_CLEAR_DEPTH, 1.0f, 0);

		
	}
	
    //
    // Present our back buffer to our front buffer
    //
	((IDXGISwapChain*&)SC.getSwapC())->Present( 0, 0 );
#endif
}


#ifdef D_DIRECTX
HRESULT CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout) {
	// Reflect shader info
	ID3D11ShaderReflection* pVertexShaderReflection = NULL;
	if (FAILED(D3DReflect(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection)))
	{
		return S_FALSE;
	}

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	pVertexShaderReflection->GetDesc(&shaderDesc);

	// Read input layout description from shader info
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	int offset = 0;
	for (int i = 0; i < shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

		// fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = offset;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT; offset += 12;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		//save element desc
		inputLayoutDesc.push_back(elementDesc);
	}

	// Try to create Input Layout
	HRESULT hr = pD3DDevice->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), pInputLayout);

	//Free allocation shader reflection memory
	pVertexShaderReflection->Release();
	return hr;
}
#endif


/*
bool DoTheImportThing(const std::string& pFile) {

	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	// If the import failed, report it
	if (!scene)
	{
		//DoTheErrorLogging(importer.GetErrorString());
		return false;
	}
	// Now we can access the file's contents.
	//DoTheSceneProcessing(scene);
	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

void CopyNodesWithMeshes(aiNode node, aiScene targetParent, mat4 accTransform) {
	aiScene parent;
	mat4 transform;
	// if node has meshes, create a new scene object for it
	if (node.mNumMeshes > 0) {
		aiScene newObject = new aiScene;
		targetParent.addChild(newObject);
		// copy the meshes
		CopyMeshes(node, newObject);
		// the new object is the parent for all child nodes
		parent = newObject;
		transform.SetUnity();
		
	}
	else  {
		// if no meshes, skip the node, but keep its transformation
		parent = targetParent;
		transform = node.mTransformation * accTransform;
	}
	// continue for all child nodes
	for (all node.mChildren)
		CopyNodesWithMeshes(node.mChildren[a], parent, transform);
}
*/

//TODO LIST
//ASSIMP

