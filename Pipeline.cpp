#include "Pipeline.h"

#include <fstream>
#include <string>
#include <iostream>

bool LoadShaders(ID3D11Device* device, ID3D11VertexShader*& vShader, ID3D11PixelShader*& pShader, std::string& vShaderByteCode)
{
	std::string shaderData;
	std::ifstream reader;
	reader.open("VertexShader.cso", std::ios::binary | std::ios::ate);
	if (!reader.is_open())
	{
		std::cerr << "Could not open VS file!" << std::endl;
		return false;
	}

	reader.seekg(0, std::ios::end);
	shaderData.reserve(static_cast<unsigned int>(reader.tellg()));
	reader.seekg(0, std::ios::beg);

	shaderData.assign((std::istreambuf_iterator<char>(reader)),
		std::istreambuf_iterator<char>());

	if (FAILED(device->CreateVertexShader(shaderData.c_str(), shaderData.length(), nullptr, &vShader)))
	{
		std::cerr << "Failed to create vertex shader!" << std::endl;
		return false;
	}
	
	vShaderByteCode = shaderData;
	shaderData.clear();
	reader.close();
	//
	reader.open("PixelShader.cso", std::ios::binary | std::ios::ate);
	if (!reader.is_open())
	{
		std::cerr << "Could not open PS file!" << std::endl;
		return false;
	}

	reader.seekg(0, std::ios::end);
	shaderData.reserve(static_cast<unsigned int>(reader.tellg()));
	reader.seekg(0, std::ios::beg);

	shaderData.assign((std::istreambuf_iterator<char>(reader)),
		std::istreambuf_iterator<char>());

	if (FAILED(device->CreatePixelShader(shaderData.c_str(), shaderData.length(), nullptr, &pShader)))
	{
		std::cerr << "Failed to create pixel shader!" << std::endl;
		return false;
	}

	return true;
}

void CreateInputLayout(ID3D11Device* device, InputLayout& inputLayout, const std::string& vShaderByteCode)
{
	inputLayout.AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	inputLayout.AddInputElement("COLOUR", DXGI_FORMAT_R32G32B32_FLOAT);
	inputLayout.FinalizeInputLayout(device, vShaderByteCode.c_str(), vShaderByteCode.size());
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
//void CreateCamera(Camera& camera, ID3D11Device* device)
//{
//	ProjectionInfo projectionInfo;
//	projectionInfo.aspectRatio = 1;
//	projectionInfo.fovAngleY = 1;
//	projectionInfo.farZ = 2;
//	projectionInfo.nearZ = 1;
//
//	//camera.MoveForward(10);
//
//	camera.Initialize(device, projectionInfo, DirectX::XMFLOAT3(0.0f, 0.0f, 2.0f));
//
//	//camera.MoveForward(10);
//
//}

bool SetupPipeline(ID3D11Device* device, VertexBuffer& vertexBuffer, ID3D11VertexShader*& vShader,
	ID3D11PixelShader*& pShader, InputLayout &inputLayout)
{
	std::string vShaderByteCode;
	if (!LoadShaders(device, vShader, pShader, vShaderByteCode))
	{
		std::cerr << "Error loading shaders!" << std::endl;
		return false;
	}

	CreateInputLayout(device, inputLayout, vShaderByteCode);

	CreateVertexBuffer(device, vertexBuffer);

	//CreateCamera(camera,device);

	return true;
}