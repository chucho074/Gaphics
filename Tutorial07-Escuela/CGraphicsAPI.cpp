#include "CGraphicsAPI.h"
#ifdef D_DIRECTX
int CGraphicsAPI::init() {
	/*HRESULT hr = S_OK;

	Device.init();

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;


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



	for (unsigned int driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, Device.getFlags(), featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &SC.getSC(), &SC.getSwapC(), &Device.getDevice(), &g_featureLevel, &DevContext.getDContext());
		if (SUCCEEDED(hr)) {
			break;
		}
	}

*/




	return 0;
}
#endif