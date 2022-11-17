#include "DepthBuffer.h"

DepthBuffer::DepthBuffer(ID3D11Device* device, UINT width, UINT height, bool hasSRV)
{

}

DepthBuffer::~DepthBuffer()
{
	if (texture)
	{
		texture->Release();
		texture = 0;
	}
	if (srv)
	{
		srv->Release();
		srv = 0;
	}
}

void DepthBuffer::Initialize(ID3D11Device* device, UINT width, UINT height, bool hasSRV, UINT arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		device->CreateDepthStencilView(0, 0, &depthStencilViews[i]);
	}
	
	if (hasSRV = true)
	{
		device->CreateShaderResourceView(0, 0, &srv);
	}
}

ID3D11DepthStencilView* DepthBuffer::GetDSV(UINT arrayIndex) const
{
    return depthStencilViews[arrayIndex];
}

ID3D11ShaderResourceView* DepthBuffer::GetSRV() const
{
    return srv;
}
