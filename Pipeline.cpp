#include "Pipeline.h"

#include <fstream>
#include <string>
#include <iostream>

void LoadShaders(ID3D11Device* device, Shader* vShader, Shader* pShader)
{
	vShader->Initialize(device, ShaderType::VERTEX_SHADER, "VertexShader.cso");
	pShader->Initialize(device, ShaderType::PIXEL_SHADER, "PixelShader.cso");
	//std::string shaderData;
	//std::ifstream reader;
	/*reader.open("VertexShader.cso", std::ios::binary | std::ios::ate);
	if (!reader.is_open())
	{
		std::cerr << "Could not open VS file!" << std::endl;
		return false;
	}*/

	//reader.seekg(0, std::ios::end);
	//shaderData.reserve(static_cast<unsigned int>(reader.tellg()));
	//reader.seekg(0, std::ios::beg);

	//shaderData.assign((std::istreambuf_iterator<char>(reader)),
	//	std::istreambuf_iterator<char>());

	//if (FAILED(device->CreateVertexShader(shaderData.c_str(), shaderData.length(), nullptr, &vShader)))
	//{
	//	std::cerr << "Failed to create vertex shader!" << std::endl;
	//	return false;
	//}
	
	//vShaderByteCode = shaderData;
	//shaderData.clear();
	//reader.close();
	////
	//reader.open("PixelShader.cso", std::ios::binary | std::ios::ate);
	//if (!reader.is_open())
	//{
	//	std::cerr << "Could not open PS file!" << std::endl;
	//	return false;
	//}

	//reader.seekg(0, std::ios::end);
	//shaderData.reserve(static_cast<unsigned int>(reader.tellg()));
	//reader.seekg(0, std::ios::beg);

	//shaderData.assign((std::istreambuf_iterator<char>(reader)),
	//	std::istreambuf_iterator<char>());

	//if (FAILED(device->CreatePixelShader(shaderData.c_str(), shaderData.length(), nullptr, &pShader)))
	//{
	//	std::cerr << "Failed to create pixel shader!" << std::endl;
	//	return false;
	//}

}

void CreateInputLayout(ID3D11Device* device, InputLayout& inputLayout, Shader* vShader)
{
	//inputLayout.AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	//inputLayout.AddInputElement("COLOUR", DXGI_FORMAT_R32G32B32_FLOAT);
	inputLayout.FinalizeInputLayout(device, vShader->GetShaderByteData(), vShader->GetShaderByteSize());
}

void CreateVertexBuffer(ID3D11Device* device, VertexBuffer& vertexBuffer)
{
	SimpleVertex triangle[] =
	{
		{ {0, 0.5f, 0.0f}, {0, 0, 1} },
		{ {0.5, -0.5f, 0.0f}, {0, 1, 0} },
		{ {-0.5, -0.5f, 0.0f}, {1, 0, 0}}
	};


	//TODO: ta bort hårdkodad antal verticer!
	vertexBuffer.Initialize(device, sizeof(triangle), 3, triangle);
}

bool SetupPipeline(ID3D11Device* device, VertexBuffer& vertexBuffer, Shader* vShader,
	Shader* pShader, InputLayout &inputLayout)
{
	

	LoadShaders(device, vShader, pShader);
	//void* vp = vShader->GetShaderByteData();
	//std::string* vShaderByteCode = static_cast<std::string*>(vShader->GetShaderByteData());

	CreateInputLayout(device, inputLayout, vShader);

	CreateVertexBuffer(device, vertexBuffer);

	return true;
}