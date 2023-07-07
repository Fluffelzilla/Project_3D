#pragma once
#include"OBJHandler.h"
class Model
{
	//ladda en model via objhandla samt spara datan
	//skapa inputlayout som passar för den modellen som laddas in
	//skapa en vertexbuffer för datan
	//kunna rendera
private:

public:
	Model(std::wstring filePath);
	void render(ID3D11DeviceContext* immediateContext, ID3D11RenderTargetView* rtv,
		ID3D11DepthStencilView* dsView, D3D11_VIEWPORT& viewport, ID3D11InputLayout* inputLayout,
		ID3D11Buffer* vertexBuffer, ID3D11Buffer* cameraBuffer, Shader& vShader, Shader& pShader);
};

