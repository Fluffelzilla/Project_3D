#pragma once
#include <d3d11_4.h>

class RenderTarget
{
private:
	ID3D11Texture2D* texture = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	ID3D11ShaderResourceView* srv = nullptr;

public:
	RenderTarget() = default;
	~RenderTarget();
	RenderTarget(const RenderTarget& other) = delete;
	RenderTarget& operator=(const RenderTarget& other) = delete;
	RenderTarget(RenderTarget&& other) = delete;
	RenderTarget& operator=(RenderTarget&& other) = delete;

	void Initialize(ID3D11Device* device, UINT width, UINT height,
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM, bool hasSRV = false);

	ID3D11RenderTargetView* GetRTV() const;
	ID3D11ShaderResourceView* GetSRV() const;
};

