#include "Mesh.h"

Mesh::Mesh(void * Device, void * DContext, std::vector<SimpleVertex>& vertices, std::vector<DWORD>& indices) {
	/*this->DContx = DContext;

	HRESULT hr = this->vertexbuffer.Initialize(device, vertices.data(), vertices.size());
	hr = this->indexbuffer.Initialize(device, indices.data(), indices.size());*/
}

Mesh::Mesh(const Mesh & inMesh) {
/*
	this->deviceContext = mesh.deviceContext;
	this->indexbuffer = mesh.indexbuffer;
	this->vertexbuffer = mesh.vertexbuffer;*/
}

void Mesh::Draw() {
	/*UINT offset = 0;
	this->deviceContext->IASetVertexBuffers(0, 1, this->vertexbuffer.GetAddressOf(), this->vertexbuffer.StridePtr(), &offset);
	this->deviceContext->IASetIndexBuffer(this->indexbuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	this->deviceContext->DrawIndexed(this->indexbuffer.BufferSize(), 0, 0);*/
}
