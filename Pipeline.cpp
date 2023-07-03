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

void CreateVertexBuffer(ID3D11Device* device, VertexBuffer& vertexBuffer, ModelHandler& mHandler)
{
	//OBJHandler objhandler;
	//objhandler.LoadFile(L"objects/otherCube.obj");
	vertexBuffer.Initialize(device,mHandler.objhandler.getByteSizeData(), mHandler.objhandler.getNrOfVertices(), mHandler.objhandler.getVecTrianglesData());
}

bool SetupPipeline(ID3D11Device* device, VertexBuffer& vertexBuffer, Shader* vShader,
	Shader* pShader, InputLayout &inputLayout, ModelHandler& mHandler)
{
	LoadShaders(device, vShader, pShader);

	CreateInputLayout(device, inputLayout, vShader);

	CreateVertexBuffer(device, vertexBuffer, mHandler);

	return true;
}