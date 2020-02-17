#include "CRenderTargetView.h"

CRenderTargetView::CRenderTargetView() {


}

CRenderTargetView::~CRenderTargetView() {



}

ID3D11RenderTargetView *& CRenderTargetView::getRTV() {
	return RTV;
}
