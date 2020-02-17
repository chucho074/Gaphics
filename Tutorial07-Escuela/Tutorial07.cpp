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


#include "CCamera.h"
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

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------

struct SimpleVertex {
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

struct CBNeverChanges {
    XMMATRIX mView;
};

struct CBChangeOnResize {
    XMMATRIX mProjection;
};

struct CBChangesEveryFrame {
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
};


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
//ID3D11Device*                       g_pd3dDevice = NULL;
//ID3D11DeviceContext*                g_pImmediateContext = NULL;
//IDXGISwapChain*                     g_pSwapChain = NULL;
//ID3D11RenderTargetView*             g_pRenderTargetView = NULL;
//ID3D11Texture2D*                    g_pDepthStencil = NULL;
//ID3D11DepthStencilView*             g_pDepthStencilView = NULL;
ID3D11VertexShader*                 g_pVertexShader = NULL;
ID3D11PixelShader*                  g_pPixelShader = NULL;
ID3D11InputLayout*                  g_pVertexLayout = NULL;
//ID3D11Buffer*                       g_pVertexBuffer = NULL;
//ID3D11Buffer*                       g_pIndexBuffer = NULL;
//ID3D11Buffer*                       g_pCBNeverChanges = NULL;
//ID3D11Buffer*                       g_pCBChangeOnResize = NULL;
//ID3D11Buffer*                       g_pCBChangesEveryFrame = NULL;
ID3D11ShaderResourceView*           g_pTextureRV = NULL;
//ID3D11SamplerState*                 g_pSamplerLinear = NULL;
XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor( 0.7f, 0.7f, 0.7f, 1.0f );

CCamera Cam;
DescCamera DescCam;
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
CDepthStencil DepthStencil;
CDepthStencilView DSView;
CRenderTargetView RTView;
CSamplerState SS;


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

    if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
        return 0;

    if( FAILED( InitDevice() ) )
    {
        CleanupDevice();
        return 0;
    }

    // Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
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
    if( !g_hWnd )
        return E_FAIL;

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

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL );
    if( FAILED(hr) )
    {
        if( pErrorBlob != NULL )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice() {

	Cam.init(DescCam);
	Device.init();

    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( g_hWnd, &rc );
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    

    D3D_DRIVER_TYPE driverTypes[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	
	
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

	
	
   

    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ ) {
        g_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain( NULL, g_driverType, NULL,Device.getFlags(), featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &SC.getSC(), &SC.getSwapC(), &Device.getDevice(), &g_featureLevel, &DevContext.getDContext());
		if (SUCCEEDED(hr)) {
			break;
		}
    }
	if (FAILED(hr)) {
		return hr;
	}

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = NULL;
    hr = SC.getSwapC()->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if (FAILED(hr)) {
		return hr;
	}

    hr = Device.getDevice()->CreateRenderTargetView( pBackBuffer, NULL, &RTView.getRTV());
	pBackBuffer->Release();
	if (FAILED(hr)) {
		return hr;
	}

    // Create depth stencil texture
    
	TextureDesc TextureDesc;
    /*ZeroMemory( &descDepth, sizeof(descDepth) );
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;*/

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

    hr = Device.getDevice()->CreateTexture2D( &DepthStencil.getDesc(), NULL, &DepthStencil.getTexture() );
    if( FAILED( hr ) )
        return hr;

    // Create the depth stencil view
    
	DSViewDesc DescDSV;


	DescDSV.Format = TextureDesc.Format;
	DescDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DescDSV.Texture2D.MipSlice = 0;

	DSView.init(DescDSV);


    hr = Device.getDevice()->CreateDepthStencilView( DepthStencil.getTexture(), &DSView.getDSVDesc(), &DSView.getDSV());
    if( FAILED( hr ) )
        return hr;

	DevContext.getDContext()->OMSetRenderTargets( 1, &RTView.getRTV(), DSView.getDSV() );

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
	DevContext.getDContext()->RSSetViewports( 1, &vp );

    // Compile the vertex shader
    ID3DBlob* pVSBlob = NULL;
    hr = CompileShaderFromFile( L"Tutorial07.fx", "VS", "vs_4_0", &pVSBlob );
    if( FAILED( hr ) ) {
        MessageBox( NULL,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

    // Create the vertex shader
    hr = Device.getDevice()->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader );
    if( FAILED( hr ) ) {    
        pVSBlob->Release();
        return hr;
    }

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE( layout );

    // Create the input layout
    hr = Device.getDevice()->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
                                          pVSBlob->GetBufferSize(), &g_pVertexLayout );
    pVSBlob->Release();
    if( FAILED( hr ) )
        return hr;

    // Set the input layout
	DevContext.getDContext()->IASetInputLayout( g_pVertexLayout );

    // Compile the pixel shader
    ID3DBlob* pPSBlob = NULL;
    hr = CompileShaderFromFile( L"Tutorial07.fx", "PS", "ps_4_0", &pPSBlob );
    if( FAILED( hr ) ) {
        MessageBox( NULL,
                    L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
        return hr;
    }

    // Create the pixel shader
    hr = Device.getDevice()->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader );
    pPSBlob->Release();
    if( FAILED( hr ) )
        return hr;

    // Create vertex buffer
    SimpleVertex vertices[] = {
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
    };

    
    ZeroMemory( &DBuffer, sizeof(DBuffer) );
	DBuffer.Usage = D3D11_USAGE_DEFAULT;
	DBuffer.CPUAccessFlags = 0;

	DBuffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	DBuffer.ByteWidth = sizeof(SimpleVertex) * 24;
	VBuffer.init(DBuffer);
	



    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory( &InitData, sizeof(InitData) );
    InitData.pSysMem = vertices;
    hr = Device.getDevice()->CreateBuffer( &VBuffer.getBD(), &InitData, &VBuffer.getB());
    if( FAILED( hr ) )
        return hr;

    // Set vertex buffer
    UINT stride = sizeof( SimpleVertex );
    UINT offset = 0;
	DevContext.getDContext()->IASetVertexBuffers( 0, 1, &VBuffer.getB(), &stride, &offset );

    // Create index buffer
    // Create vertex buffer
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

	DBuffer.ByteWidth = sizeof(SimpleVertex) * 24;
	DBuffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IBuffer.init(DBuffer);
    
    InitData.pSysMem = indices;
    hr = Device.getDevice()->CreateBuffer( &IBuffer.getBD(), &InitData, &IBuffer.getB());
    if( FAILED( hr ) )
        return hr;

    // Set index buffer
	DevContext.getDContext()->IASetIndexBuffer(IBuffer.getB(), DXGI_FORMAT_R16_UINT, 0 );

    // Set primitive topology
	DevContext.getDContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    // Create the constant buffers
	
	
	DBuffer.ByteWidth = sizeof(CBNeverChanges);
	DBuffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CBuffer_NC.init(DBuffer);

    hr = Device.getDevice()->CreateBuffer( &CBuffer_NC.getBD(), NULL, &CBuffer_NC.getB());
    if( FAILED( hr ) )
        return hr;
    
	DBuffer.ByteWidth = sizeof(CBChangeOnResize);
	CBuffer_CoR.init(DBuffer);
    hr = Device.getDevice()->CreateBuffer( &CBuffer_CoR.getBD(), NULL, &CBuffer_CoR.getB());
    if( FAILED( hr ) )
        return hr;
    
	DBuffer.ByteWidth = sizeof(CBChangesEveryFrame);
	CBuffer_CEF.init(DBuffer);
    hr = Device.getDevice()->CreateBuffer( &CBuffer_CEF.getBD(), NULL, &CBuffer_CEF.getB());
    if( FAILED( hr ) )
        return hr;

    // Load the Texture
    hr = D3DX11CreateShaderResourceViewFromFile(Device.getDevice(), L"seafloor.dds", NULL, NULL, &g_pTextureRV, NULL );
    if( FAILED( hr ) )
        return hr;

    // Create the sample state
	SamplerDesc sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
    sampDesc.Filter =			D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU =			D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV =			D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW =			D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc =	D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD =			0;
    sampDesc.MaxLOD =			D3D11_FLOAT32_MAX;

	SS.init(sampDesc);
    hr = Device.getDevice()->CreateSamplerState( &SS.getSSDesc(), &SS.getSS() );
    if( FAILED( hr ) )
        return hr;

    // Initialize the world matrices
    g_World = XMMatrixIdentity();

	DescCam.W = (rc.right - rc.left);
	DescCam.H = (rc.bottom - rc.top);
	DescCam.Fov = XM_PIDIV4;
	DescCam.Near = 0.01f;
	DescCam.Far = 100.f;

	Cam.update(DescCam);

    CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = XMMatrixTranspose(Cam.getVM());
	DevContext.getDContext()->UpdateSubresource(CBuffer_NC.getB(), 0, NULL, &cbNeverChanges, 0, 0 );

    // Initialize the projection matrix
    g_Projection = XMMatrixPerspectiveFovLH(DescCam.Fov, (DescCam.W / DescCam.H), DescCam.Near, DescCam.Far);
    
    CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = XMMatrixTranspose( g_Projection );
	DevContext.getDContext()->UpdateSubresource(CBuffer_CoR.getB(), 0, NULL, &cbChangesOnResize, 0, 0 );

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice() {
    if(DevContext.getDContext()) DevContext.getDContext()->ClearState();

    if( SS.getSS() ) SS.getSS()->Release();
    if( g_pTextureRV ) g_pTextureRV->Release();
    if( CBuffer_NC.getB() ) CBuffer_NC.getB()->Release();
    if( CBuffer_CoR.getB() ) CBuffer_CoR.getB()->Release();
    if( CBuffer_CEF.getB() ) CBuffer_CEF.getB()->Release();
    if( VBuffer.getB() ) VBuffer.getB()->Release();
    if( IBuffer.getB() ) IBuffer.getB()->Release();
    if( g_pVertexLayout ) g_pVertexLayout->Release();
    if( g_pVertexShader ) g_pVertexShader->Release();
    if( g_pPixelShader ) g_pPixelShader->Release();
    if( DepthStencil.getTexture() ) DepthStencil.getTexture()->Release();
    if( DSView.getDSV() ) DSView.getDSV()->Release();
    if(RTView.getRTV()) RTView.getRTV()->Release();
    if(SC.getSwapC()) SC.getSwapC()->Release();
    if(DevContext.getDContext()) DevContext.getDContext()->Release();
    if(Device.getDevice()) Device.getDevice()->Release();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
    PAINTSTRUCT ps;
    HDC hdc;

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
		case WM_SIZING: {

			RECT rc;
			GetClientRect(g_hWnd, &rc);
			DescCam.W = (rc.right - rc.left);
			DescCam.H = (rc.bottom - rc.top);
			Cam.update(DescCam);

			g_Projection = XMMatrixPerspectiveFovLH(DescCam.Fov, (DescCam.W / DescCam.H), DescCam.Near, DescCam.Far);

			CBChangeOnResize cbChangesOnResize;
			cbChangesOnResize.mProjection = XMMatrixTranspose( g_Projection );
			DevContext.getDContext()->UpdateSubresource(CBuffer_CoR.getB(), 0, NULL, &cbChangesOnResize, 0, 0);

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
    g_World = XMMatrixRotationY( t );

    // Modify the color
    g_vMeshColor.x = ( sinf( t * 1.0f ) + 1.0f ) * 0.5f;
    g_vMeshColor.y = ( cosf( t * 3.0f ) + 1.0f ) * 0.5f;
    g_vMeshColor.z = ( sinf( t * 5.0f ) + 1.0f ) * 0.5f;

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	DevContext.getDContext()->ClearRenderTargetView(RTView.getRTV(), ClearColor );

	//DevContext.getDContext()->ClearRenderTargetView(  );

    //
    // Clear the depth buffer to 1.0 (max depth)
    //
	DevContext.getDContext()->ClearDepthStencilView( DSView.getDSV(), D3D11_CLEAR_DEPTH, 1.0f, 0 );

    //
    // Update variables that change once per frame
    //
    CBChangesEveryFrame cb;
    cb.mWorld = XMMatrixTranspose( g_World );
    cb.vMeshColor = g_vMeshColor;
	DevContext.getDContext()->UpdateSubresource(CBuffer_CEF.getB(), 0, NULL, &cb, 0, 0 );

    //
    // Render the cube
    //
	DevContext.getDContext()->VSSetShader( g_pVertexShader, NULL, 0 );
	DevContext.getDContext()->VSSetConstantBuffers( 0, 1, &CBuffer_NC.getB());
	DevContext.getDContext()->VSSetConstantBuffers( 1, 1, &CBuffer_CoR.getB());
	DevContext.getDContext()->VSSetConstantBuffers( 2, 1, &CBuffer_CEF.getB());
	DevContext.getDContext()->PSSetShader( g_pPixelShader, NULL, 0 );
	DevContext.getDContext()->PSSetConstantBuffers( 2, 1, &CBuffer_CEF.getB());
	DevContext.getDContext()->PSSetShaderResources( 0, 1, &g_pTextureRV );
	DevContext.getDContext()->PSSetSamplers( 0, 1, &SS.getSS() );
	DevContext.getDContext()->DrawIndexed( 36, 0, 0 );

    //
    // Present our back buffer to our front buffer
    //
	SC.getSwapC()->Present( 0, 0 );
}
