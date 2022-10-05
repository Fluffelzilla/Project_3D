#include <Windows.h>
#include <iostream>
#include <d3d11.h>
#include "Window.h"
#include "D3D11_imp.h"
#include "Pipeline.h"
#include<DirectXMath.h>

//Graphics header includes:
#include "DeraImGui/imgui.h"
#include "DeraImGui/imgui_impl_dx11.h"
#include "DeraImGui/imgui_impl_win32.h"

void Render(ID3D11DeviceContext* immediateContext, ID3D11RenderTargetView* rtv,
	ID3D11DepthStencilView* dsView, D3D11_VIEWPORT& viewport, ID3D11VertexShader* vShader,
	ID3D11PixelShader* pShader, ID3D11InputLayout* inputLayout, ID3D11Buffer* vertexBuffer)
{
	float clearColour[4] = { 0, 0, 0, 0 };
	immediateContext->ClearRenderTargetView(rtv, clearColour);
	immediateContext->ClearDepthStencilView(dsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
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
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* vertexBuffer;

	if (!SetupD3D11(WIDTH, HEIGHT, window, device, immediateContext, swapChain, rtv, dsTexture, dsView, viewport))
	{
		std::cerr << "Failed to setup d3d11!" << std::endl;
		return -1;
	}

	if (!SetupPipeline(device, vertexBuffer, vShader, pShader, inputLayout))
	{
		std::cerr << "Failed to setup pipeline!" << std::endl;
		return -1;
	}

	//Set up GUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, immediateContext);
	ImGui::StyleColorsDark();

	MSG msg = { };

	//test world space settings
	//fungerar ej... ska kopplas till constant buffer vilket jag inte har. samt att uppdatering av scenen under körning (tid) inte är implementerad
	static float translationOffset[3] = { 0,0,0 };
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(translationOffset[0], translationOffset[1], translationOffset[2]);

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Render(immediateContext, rtv, dsView, viewport, vShader, pShader, inputLayout, vertexBuffer);

		//Start Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//Create ImGui Test Window
		ImGui::Begin("Scene Setings");
		ImGui::Text("Triangle position word");
		ImGui::DragFloat3("Translation X/Y/Z", translationOffset, 0.1f, -5.0f, 5.0f);
		ImGui::End();

		//Assemble Together Draw Data
		ImGui::Render();

		//Render Draw Data
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


		swapChain->Present(0, 0);
	}

	vertexBuffer->Release();
	inputLayout->Release();
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