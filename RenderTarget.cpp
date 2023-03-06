#include "RenderTarget.h"

RenderTarget::~RenderTarget()
{
	if (texture!=nullptr)
	{
		texture->Release();
		texture = 0;
	}
	if (rtv != nullptr)
	{
		rtv->Release();
		rtv = 0;
	}
	if (srv != nullptr)
	{
		srv->Release();
		srv = 0;
	}
}

void RenderTarget::Initialize(ID3D11Device* device, UINT width, UINT height, DXGI_FORMAT format, bool hasSRV)
{
	//TODO: kolla om textueDesc. information stämmer utifrån mitt behov!!
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = format;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	device->CreateTexture2D(&textureDesc, nullptr, &texture);

	if (hasSRV==true)
	{
		device->CreateShaderResourceView(texture, nullptr, &srv);
	}

	device->CreateRenderTargetView(texture, nullptr, &rtv);
}

ID3D11RenderTargetView* RenderTarget::GetRTV() const
{
	return rtv;
}

ID3D11ShaderResourceView* RenderTarget::GetSRV() const
{
	return srv;
}
