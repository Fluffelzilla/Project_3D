#include <Windows.h>
#include <iostream>
#include <d3d11.h>

#include "Window.h"
#include "D3D11_imp.h"
#include "Pipeline.h"

#include "TimeHandler.h"

#include "InputLayout.h"
#include "VertexBuffer.h" 
#include "Camera.h"
void Render(ID3D11DeviceContext* immediateContext, ID3D11RenderTargetView* rtv,
	ID3D11DepthStencilView* dsView, D3D11_VIEWPORT& viewport, ID3D11VertexShader* vShader,
	ID3D11PixelShader* pShader, ID3D11InputLayout* inputLayout, ID3D11Buffer* vertexBuffer, ID3D11Buffer* cameraBuffer)
{
	float clearColour[4] = { 0, 0, 0, 0 };
	immediateContext->ClearRenderTargetView(rtv, clearColour);
	immediateContext->ClearDepthStencilView(dsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	immediateContext->VSSetConstantBuffers(0, 1, &cameraBuffer);
	//immediateContext->PSSetConstantBuffers(1, 1, &cameraBuffer);
	immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	immediateContext->IASetInputLayout(inputLayout);
	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	immediateContext->VSSetShader(vShader, nullptr, 0);
	immediateContext->RSSetViewports(1, &viewport);
	immediateContext->PSSetShader(pShader, nullptr, 0);
	immediateContext->OMSetRenderTargets(1, &rtv, dsView);

	immediateContext->Draw(3, 0);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	const UINT WIDTH = 1024;
	const UINT HEIGHT = 576;
	HWND window;

	if (!SetupWindow(hInstance, WIDTH, HEIGHT, nCmdShow, window))
	{
		std::cerr << "Failed to setup window!" << std::endl;
		return -1;
	}

	ID3D11Device* device;
	ID3D11DeviceContext* immediateContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;
	ID3D11Texture2D* dsTexture;
	ID3D11DepthStencilView* dsView;
	D3D11_VIEWPORT viewport;
	ID3D11VertexShader* vShader;
	ID3D11PixelShader* pShader;

	InputLayout inputLayout;
	VertexBuffer vertexBuffer;





	if (!SetupD3D11(WIDTH, HEIGHT, window, device, immediateContext, swapChain, rtv, dsTexture, dsView, viewport))
	{
		std::cerr << "Failed to setup d3d11!" << std::endl;
		return -1;
	}

	if (!SetupPipeline(device, vertexBuffer, vShader, pShader,inputLayout))
	{
		std::cerr << "Failed to setup pipeline!" << std::endl;
		return -1;
	}

	ProjectionInfo projectionInfo;
	projectionInfo.aspectRatio = (float)WIDTH/(float)HEIGHT;
	projectionInfo.fovAngleY = 0.4 * 3.14f;
	projectionInfo.farZ = 1000.0f;
	projectionInfo.nearZ = 0.1f;

	Camera camera(device, projectionInfo, DirectX::XMFLOAT3(0.0f,0.0f,-2.0f));

	EngineUtils::TimeHandler* clock = EngineUtils::TimeHandler::instance();
	float frameRate = 60.0f;
	float elapsedTime = 0.0f;
	int frames = 0;

	MSG msg = { };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		clock->tick();
		clock->reset();
		elapsedTime += clock->deltaTime();
		frames++;
		if (elapsedTime >= 0.01f)
		{
			camera.UpdateInternalConstantBuffer(immediateContext);
			Render(immediateContext, rtv, dsView, viewport, vShader, pShader, inputLayout.GetInputLayout(), vertexBuffer.GetBuffer(), camera.GetConstantBuffer());
			swapChain->Present(0, 0);
			elapsedTime = 0.0f;
			frames = 0;
		}


	}

	EngineUtils::TimeHandler::release();
	pShader->Release();
	vShader->Release();
	dsView->Release();
	dsTexture->Release();
	rtv->Release();
	swapChain->Release();
	immediateContext->Release();
	device->Release();

	return 0;
}