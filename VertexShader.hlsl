//cbuffer cBuffer
//{
//	float xOffset;
//	float yOffset;
//};

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

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	output.position = float4(input.position, 1.0f);
	output.colour = input.colour;
	return output;
}