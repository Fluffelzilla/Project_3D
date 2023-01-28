#include "SpotLightCollection.h"

void SpotLightCollection::Initialize(ID3D11Device* device, const SpotLightData& lightInfo)
{
	SpotLightData spotData;
	
	spotData.perLightInfo = lightInfo.perLightInfo;
	spotData.shadowMapInfo = lightInfo.shadowMapInfo;
	lightBuffer.Initialize(device, sizeof(spotData.perLightInfo), spotData.perLightInfo.size());
	//TODO: behöver hight och width i shadowmap initialize!!!!
	shadowMaps.Initialize(device, 0, 0);
}

void SpotLightCollection::UpdateLightBuffers(ID3D11DeviceContext* context)
{
	//TODO:är bufferdata rätt och inehåller den rätt saker?
	lightBuffer.UpdateBuffer(context, &bufferData);
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
