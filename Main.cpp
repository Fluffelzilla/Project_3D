#include <Windows.h>
#include <iostream>
#include <d3d11.h>

#include "Window.h"
#include "D3D11_imp.h"
#include "Pipeline.h"

#include "TimeHandler.h"
#include"OBJHandler.h"
#include "InputLayout.h"
#include "VertexBuffer.h" 
#include "Camera.h"
#include "shader.h"

void Render(ID3D11DeviceContext* immediateContext, ID3D11RenderTargetView* rtv,
	ID3D11DepthStencilView* dsView, D3D11_VIEWPORT& viewport, ID3D11InputLayout* inputLayout,
	ID3D11Buffer* vertexBuffer, ID3D11Buffer* cameraBuffer,Shader& vShader,Shader& pShader)
{
	UINT stride = sizeof(Normal) + sizeof(TextureCoordinate) + sizeof(Position);
	UINT offset = 0;
	float clearColour[4] = { 0, 0, 0, 0 };
	immediateContext->ClearRenderTargetView(rtv, clearColour);
	immediateContext->ClearDepthStencilView(dsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	immediateContext->VSSetConstantBuffers(0, 1, &cameraBuffer);
	immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	immediateContext->IASetInputLayout(inputLayout);
	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	immediateContext->RSSetViewports(1, &viewport);
	immediateContext->OMSetRenderTargets(1, &rtv, dsView);
	vShader.BindShader(immediateContext);
	pShader.BindShader(immediateContext);

	immediateContext->Draw(36, 0);
}

void MoveCamera(Camera& camera)
{
	int w = 119;
	int a = 97;
	int s = 115;
	int d = 100;

	float amount = 0.2f;

	if ((GetKeyState(a) & 0x8000 || GetKeyState(0x41) & 0x8000))
	{
		camera.MoveRight(-amount);
	}

	else if ((GetKeyState(d) & 0x8000 || GetKeyState(0x44) & 0x8000))
	{
		camera.MoveRight(amount);
	}

	if ((GetKeyState(w) & 0x8000 || GetKeyState(0x57) & 0x8000))
	{
		camera.MoveForward(amount);
	}

	else if ((GetKeyState(s) & 0x8000 || GetKeyState(0x53) & 0x8000))
	{
		camera.MoveForward(-amount);
	}

	if ((GetKeyState(VK_CONTROL) & 0x8000))
	{
		camera.MoveUp(-amount);
	}

	else if ((GetKeyState(VK_SPACE) & 0x8000 ) )
	{
		camera.MoveUp(amount);
	}

	if ((GetKeyState(VK_RIGHT) & 0x8000))
	{
		camera.RotateRight(amount / 10);
	}

	else if ((GetKeyState(VK_LEFT) & 0x8000))
	{
		camera.RotateRight(-amount / 10);
	}

	if ((GetKeyState(VK_UP) & 0x8000))
	{
		camera.RotateUp(amount / 10);
	}

	else if ((GetKeyState(VK_DOWN) & 0x8000))
	{
		camera.RotateUp(-amount / 10);
	}
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
	InputLayout inputLayout;
	VertexBuffer vertexBuffer;
	Shader vertexShader;
	Shader pixelShader;

	if (!SetupD3D11(WIDTH, HEIGHT, window, device, immediateContext, swapChain, rtv, dsTexture, dsView, viewport))
	{
		std::cerr << "Failed to setup d3d11!" << std::endl;
		return -1;
	}

	if (!SetupPipeline(device, vertexBuffer, &vertexShader, &pixelShader, inputLayout))
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
			MoveCamera(camera);
			camera.UpdateInternalConstantBuffer(immediateContext);

			Render(immediateContext, rtv, dsView, viewport, inputLayout.GetInputLayout(), vertexBuffer.GetBuffer(), camera.GetConstantBuffer(),vertexShader,pixelShader);
			swapChain->Present(0, 0);
			elapsedTime = 0.0f;
			frames = 0;

		}

	}

	EngineUtils::TimeHandler::release();

	dsView->Release();
	dsTexture->Release();
	rtv->Release();
	swapChain->Release();
	immediateContext->Release();
	device->Release();

	return 0;
}