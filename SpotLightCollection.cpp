#include "SpotLightCollection.h"

void SpotLightCollection::Initialize(ID3D11Device* device, const SpotLightData& lightInfo)
{
	//lightInfo.perLightInfo.size();
	//lightBuffer.Initialize(device, lightInfo.perLightInfo.size(),)
}

void SpotLightCollection::UpdateLightBuffers(ID3D11DeviceContext* context)
{

	//TODO: assign acutal data insted of nullptr!!!
	lightBuffer.UpdateBuffer(context, nullptr);
}

UINT SpotLightCollection::GetNrOfLights() const
{
	return lightBuffer.GetNrOfElements();
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
	return shadowCameras[lightIndex].GetConstantBuffer();
}
