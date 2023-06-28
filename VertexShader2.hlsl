
struct VertexShaderInput
{
	float3 position : POSITION;
	float2 texcoor : TEXCOORD;
	float3 normal : NORMAL;
};

struct VertexShaderOutput
{
	float4 position : SV_POSITION;
	float4 texcoor : TEXCOORD;
	
};

cbuffer camerabuffer
{
	matrix world;
	matrix viewPro;
	float3 cPosition;
};

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	output.position = float4(input.position, 1.0f);
	output.position = mul(output.position, world);
	output.position = mul(output.position, viewPro);
	output.texcoor = float4(input.texcoor, 1.0f, 1.0f);
	
	return output;
}