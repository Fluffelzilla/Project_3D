#include "DepthBuffer.h"

DepthBuffer::DepthBuffer(ID3D11Device* device, UINT width, UINT height, bool hasSRV)
{
	Initialize(device, width, height, hasSRV);
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
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	device->CreateTexture2D(&textureDesc, nullptr, &texture);

	for (int i = 0; i < arraySize; i++)
	{
		device->CreateDepthStencilView(texture, 0, &depthStencilViews[i]);
	}

	if (hasSRV = true)
	{
		//ska det vara 0?
		device->CreateShaderResourceView(texture, 0, &srv);
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
