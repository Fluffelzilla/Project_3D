struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float2 texcoor : TEXCOORD;
	float3 normal : NORMAL;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	return float4(1.0f,1.0f,1.0f,1.0f);
}