#pragma once
#include <array>
#include <d3d11.h>
#include "InputLayout.h"
#include "VertexBuffer.h" 
#include"Shader.h"
//#include"OBJHandler.h"
#include"ModelHandler.h"

bool SetupPipeline(ID3D11Device* device, VertexBuffer& vertexBuffer, Shader* vShader, Shader* pShader, InputLayout& inputLayout, ModelHandler& mHandler);
