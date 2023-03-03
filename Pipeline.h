#pragma once

#include <array>
#include <d3d11.h>
#include "InputLayout.h"
#include "VertexBuffer.h" 
#include"Shader.h"
//#include "Camera.h"

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

bool SetupPipeline(ID3D11Device* device, VertexBuffer& vertexBuffer, Shader* vShader, Shader* pShader, InputLayout& inputLayout);
