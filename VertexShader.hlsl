
struct VertexShaderInput
{
	float3 position : POSITION;
	float3 colour : COLOUR;
};

struct VertexShaderOutput
{
	float4 position : SV_POSITION;
	float3 colour : COLOUR;
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
	//output.position = mul(output.position, world);
	//output.position = mul(output.position, viewPro);
	output.colour = input.colour;
	return output;
}