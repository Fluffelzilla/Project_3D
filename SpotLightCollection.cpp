#include "SpotLightCollection.h"

void SpotLightCollection::Initialize(ID3D11Device* device, const SpotLightData& lightInfo)
{
	
}

void SpotLightCollection::UpdateLightBuffers(ID3D11DeviceContext* context)
{
}

UINT SpotLightCollection::GetNrOfLights() const
{
	return 0;
}

ID3D11DepthStencilView* SpotLightCollection::GetShadowMapDSV(UINT lightIndex) const
{
	return shadowMaps.GetDSV(lightIndex);
}

ID3D11ShaderResourceView* SpotLightCollection::GetShadowMapsSRV() const
{
	return shadowMaps.GetSRV();
}

ID3D11ShaderResourceView* SpotLightCollection::GetLightBufferSRV() const
{
	return lightBuffer.GetSRV();
}

ID3D11Buffer* SpotLightCollection::GetLightCameraConstantBuffer(UINT lightIndex) const
{
	return nullptr;
}
