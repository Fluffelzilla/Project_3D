#pragma once
#include <d3d11_4.h>

class ShaderResourceTexture
{
private:
	ID3D11Texture2D* texture = nullptr;
	ID3D11ShaderResourceView* srv = nullptr;

public:
	ShaderResourceTexture() = default;
	ShaderResourceTexture(ID3D11Device* device, UINT width, UINT height, void* textureData);
	ShaderResourceTexture(ID3D11Device* device, const char* pathToTextureFile);
	~ShaderResourceTexture();
	ShaderResourceTexture(const ShaderResourceTexture& other) = delete;
	ShaderResourceTexture& operator=(const ShaderResourceTexture& other) = delete;
	ShaderResourceTexture(ShaderResourceTexture&& other) = delete;
	ShaderResourceTexture& operator=(ShaderResourceTexture&& other) = delete;

	void Initialize(ID3D11Device* device, UINT width, UINT height, void* textureData);
	void Initialize(ID3D11Device* device, const char* pathToTextureFile);

	ID3D11ShaderResourceView* GetSRV() const;
};

