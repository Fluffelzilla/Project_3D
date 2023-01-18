#include "Sampler.h"

Sampler::Sampler(ID3D11Device* device, D3D11_TEXTURE_ADDRESS_MODE adressMode, std::optional<std::array<float, 4>> borderColour)
{
}

Sampler::~Sampler()
{
}

void Sampler::Initialize(ID3D11Device* device, D3D11_TEXTURE_ADDRESS_MODE adressMode, std::optional<std::array<float, 4>> borderColour)
{
}

ID3D11SamplerState* Sampler::GetSamplerState() const
{
	return nullptr;
}
