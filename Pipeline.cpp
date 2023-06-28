#include "Pipeline.h"

#include <fstream>
#include <string>
#include <iostream>

void LoadShaders(ID3D11Device* device, Shader* vShader, Shader* pShader)
{
	vShader->Initialize(device, ShaderType::VERTEX_SHADER, "VertexShader2.cso");
	//vShader->Initialize(device, ShaderType::VERTEX_SHADER, "VertexShader.cso");
	pShader->Initialize(device, ShaderType::PIXEL_SHADER, "PixelShader.cso");
}

void CreateInputLayout(ID3D11Device* device, InputLayout& inputLayout, Shader* vShader)
{
	inputLayout.FinalizeInputLayout(device, vShader->GetShaderByteData(), vShader->GetShaderByteSize());
}

void CreateVertexBuffer(ID3D11Device* device, VertexBuffer& vertexBuffer)
{
	//SimpleVertex triangle[] =
	//{
	//	{ {0, 0.5f, 0.0f}, {0, 0, 1} },
	//	{ {0.5, -0.5f, 0.0f}, {0, 1, 0} },
	//	{ {-0.5, -0.5f, 0.0f}, {1, 0, 0}}
	//};
	//TODO: ta bort hårdkodad antal verticer!
	//vertexBuffer.Initialize(device, sizeof(triangle), 3, triangle);

	OBJHandler objhandler;
	objhandler.LoadFile(L"objects/cube.obj");
	//Triangle triss[] =
	//{
	//	objhandler.getVecTriangles()[0],
	//	objhandler.getVecTriangles()[1]
	//};
	vertexBuffer.Initialize(device, objhandler.getByteSizeData(), objhandler.getVecTriangles().size() * 3, objhandler.getVecTrianglesData());
}

bool SetupPipeline(ID3D11Device* device, VertexBuffer& vertexBuffer, Shader* vShader,
	Shader* pShader, InputLayout &inputLayout)
{
	LoadShaders(device, vShader, pShader);

	CreateInputLayout(device, inputLayout, vShader);

	CreateVertexBuffer(device, vertexBuffer);

	return true;
}