#pragma once

#include <array>
#include <d3d11.h>

struct SimpleVertex
{
	float pos[3];
	float clr[3];

	SimpleVertex(const std::array<float, 3>& position, const std::array<float, 3>& colour)
	{
		for (int i = 0; i < 3; ++i)
		{
			pos[i] = position[i];
			clr[i] = colour[i];
		}
	}
};

struct constBufferVertexShader
{
	float xOffset = 0;
	float yOffset = 0;
};

bool SetupPipeline(ID3D11Device* device, ID3D11Buffer*& vertexBuffer, ID3D11VertexShader*& vShader, ID3D11PixelShader*& pShader, ID3D11InputLayout*& inputLayout, ID3D11Buffer*& constBuffer);
