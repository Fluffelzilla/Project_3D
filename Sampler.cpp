#include "Sampler.h"

Sampler::Sampler(ID3D11Device* device, D3D11_TEXTURE_ADDRESS_MODE adressMode, std::optional<std::array<float, 4>> borderColour)
{
	Initialize(device, adressMode,borderColour);
}

Sampler::~Sampler()
{
	if (sampler!=nullptr)
	{
		sampler->Release();
		sampler = 0;
	}
}

void Sampler::Initialize(ID3D11Device* device, D3D11_TEXTURE_ADDRESS_MODE adressMode, std::optional<std::array<float, 4>> borderColour)
{
	//TODO: kolla att bordercolor och adress mode är rätt inmatade!!
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = adressMode; 
	samplerDesc.AddressV = adressMode;
	samplerDesc.AddressW = adressMode;
	samplerDesc.MipLODBias = 0.0f; 
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = borderColour.value().at(0);
	samplerDesc.BorderColor[1] = borderColour.value().at(1);
	samplerDesc.BorderColor[2] = borderColour.value().at(2);
	samplerDesc.BorderColor[3] = borderColour.value().at(3);
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	device->CreateSamplerState(&samplerDesc, &sampler);
}

ID3D11SamplerState* Sampler::GetSamplerState() const
{
	return sampler;
}
