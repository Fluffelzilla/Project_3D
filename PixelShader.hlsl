struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float3 colour : COLOUR;
};

cbuffer cameraBuffer
{
	matrix world;
	matrix viewPro;
	float3 cPosition;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	return float4(input.colour, 1.0f);
}