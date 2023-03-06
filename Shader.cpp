#include "Shader.h"
#include <fstream>
#include <iostream>

Shader::~Shader()
{
	//if (shaderByteCode)
	//{
	//	delete(shaderByteCode);
	//	shaderByteCode = 0;
	//}

	if (shader.vertex)
	{
		shader.vertex->Release();
		shader.vertex = 0;
	}
	if (shader.compute)
	{
		shader.compute->Release();
		shader.compute = 0;
	}
	if (shader.domain)
	{
		shader.domain->Release();
		shader.domain = 0;
	}
	if (shader.geometry)
	{
		shader.geometry->Release();
		shader.geometry = 0;
	}
	if (shader.hull)
	{
		shader.hull->Release();
		shader.hull = 0;
	}
	if (shader.pixel)
	{
		shader.pixel->Release();
		shader.pixel = 0;
	}

}

Shader::Shader(ID3D11Device* device, ShaderType shaderType, const void* dataPtr, size_t dataSize)
	:type(shaderType)
{
	Initialize(device, type, dataPtr, dataSize);
}

Shader::Shader(ID3D11Device* device, ShaderType shaderType, const char* csoPath)
	:type(shaderType)
{
	Initialize(device, type, csoPath);
}

void Shader::Initialize(ID3D11Device* device, ShaderType shaderType, const void* dataPtr, size_t dataSize)
{
	HRESULT hr;
	if (shaderType == ShaderType::VERTEX_SHADER)
	{
		type = ShaderType::VERTEX_SHADER;
		hr = device->CreateVertexShader(dataPtr, dataSize, nullptr, &shader.vertex);
	}

	if (shaderType == ShaderType::HULL_SHADER)
	{
		type = ShaderType::HULL_SHADER;
		hr = device->CreateHullShader(dataPtr, dataSize, nullptr, &shader.hull);
	}

	if (shaderType == ShaderType::DOMAIN_SHADER)
	{
		type = ShaderType::DOMAIN_SHADER;
		hr = device->CreateDomainShader(dataPtr, dataSize, nullptr, &shader.domain);
	}

	if (shaderType == ShaderType::GEOMETRY_SHADER)
	{
		type = ShaderType::GEOMETRY_SHADER;
		hr = device->CreateGeometryShader(dataPtr, dataSize, nullptr, &shader.geometry);
	}

	if (shaderType == ShaderType::PIXEL_SHADER)
	{
		type = ShaderType::PIXEL_SHADER;
		hr = device->CreatePixelShader(dataPtr, dataSize, nullptr, &shader.pixel);
	}

	if (shaderType == ShaderType::COMPUTE_SHADER)
	{
		type = ShaderType::COMPUTE_SHADER;
		hr=device->CreateComputeShader(dataPtr, dataSize, nullptr, &shader.compute);
	}

}

void Shader::Initialize(ID3D11Device* device, ShaderType shaderType, const char* csoPath)
{

	std::string shaderData;
	std::ifstream reader;
	reader.open(csoPath, std::ios::binary | std::ios::ate);
	if (!reader.is_open())
	{
		std::cerr << "Could not open VS file!" << std::endl;
	}
	reader.seekg(0, std::ios::end);
	shaderData.reserve(static_cast<unsigned int>(reader.tellg()));
	reader.seekg(0, std::ios::beg);

	shaderData.assign((std::istreambuf_iterator<char>(reader)),
		std::istreambuf_iterator<char>());

	shaderByteCode = new std::string(shaderData);
	//size_t length = shaderByteCode->length(); 
	Initialize(device, shaderType, shaderData.c_str(), shaderData.length());

	shaderData.clear();
	reader.close();
}

const void* Shader::GetShaderByteData() const
{
	return shaderByteCode->c_str();
}

size_t Shader::GetShaderByteSize() const
{
	return shaderByteCode->length();
}

void Shader::BindShader(ID3D11DeviceContext* context) const
{
	if (type == ShaderType::VERTEX_SHADER)
	{
		context->VSSetShader(shader.vertex, nullptr, 0);
	}

	if (type == ShaderType::HULL_SHADER)
	{
		context->HSSetShader(shader.hull, nullptr, 0);
	}

	if (type == ShaderType::DOMAIN_SHADER)
	{
		context->DSSetShader(shader.domain, nullptr, 0);
	}

	if (type == ShaderType::GEOMETRY_SHADER)
	{
		context->GSSetShader(shader.geometry, nullptr, 0);
	}

	if (type == ShaderType::PIXEL_SHADER)
	{
		context->PSSetShader(shader.pixel, nullptr, 0);
	}

	if (type==ShaderType::COMPUTE_SHADER)
	{
		context->CSSetShader(shader.compute, nullptr, 0);
	}
}
