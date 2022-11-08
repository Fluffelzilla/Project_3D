#include "Shader.h"
#include <fstream>
#include <string>
#include <iostream>

Shader::~Shader()
{
	if (shaderBlob)
	{
		shaderBlob->Release();
		shaderBlob = 0;
	}

}

Shader::Shader(ID3D11Device* device, ShaderType shaderType, const void* dataPtr, size_t dataSize)
{
	type = shaderType;

}

Shader::Shader(ID3D11Device* device, ShaderType shaderType, const char* csoPath)
{

}

void Shader::Initialize(ID3D11Device* device, ShaderType shaderType, const void* dataPtr, size_t dataSize)
{
	if (shaderType == ShaderType::VERTEX_SHADER)
	{
		device->CreateVertexShader(dataPtr, dataSize, nullptr, &shader.vertex);
	}

	if (shaderType == ShaderType::HULL_SHADER)
	{
		device->CreateHullShader(dataPtr, dataSize, nullptr, &shader.hull);
	}

	if (shaderType == ShaderType::DOMAIN_SHADER)
	{
		device->CreateDomainShader(dataPtr, dataSize, nullptr, &shader.domain);
	}

	if (shaderType == ShaderType::GEOMETRY_SHADER)
	{
		device->CreateGeometryShader(dataPtr, dataSize, nullptr, &shader.geometry);
	}

	if (shaderType == ShaderType::PIXEL_SHADER)
	{
		device->CreatePixelShader(dataPtr, dataSize, nullptr, &shader.pixel);
	}

	if (shaderType == ShaderType::COMPUTE_SHADER)
	{
		device->CreateComputeShader(dataPtr, dataSize, nullptr, &shader.compute);
	}
}

void Shader::Initialize(ID3D11Device* device, ShaderType shaderType, const char* csoPath)
{
	std::string shaderData;
	std::ifstream reader;
	reader.open(csoPath, std::ios::binary | std::ios::ate);
	//if (!reader.is_open())
	//{
	//	std::cerr << "Could not open VS file!" << std::endl;
	//	return false;
	//}
	reader.seekg(0, std::ios::end);
	shaderData.reserve(static_cast<unsigned int>(reader.tellg()));
	reader.seekg(0, std::ios::beg);

	shaderData.assign((std::istreambuf_iterator<char>(reader)),
		std::istreambuf_iterator<char>());

	//vShaderByteCode = shaderData;
	shaderData.clear();
	reader.close();

}

const void* Shader::GetShaderByteData() const
{
	return nullptr;
}

size_t Shader::GetShaderByteSize() const
{
	return size_t();
}

void Shader::BindShader(ID3D11DeviceContext* context) const
{
}
