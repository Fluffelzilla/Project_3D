cbuffer cBuffer : register(b0)
{
	float xOffset;
	float yOffset;
};

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
	input.position.x += xOffset;
	input.position.y += yOffset;
	output.position = float4(input.position, 1.0f);
	output.colour = input.colour;
	return output;
}