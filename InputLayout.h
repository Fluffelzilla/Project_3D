#pragma once
#include <string>
#include <vector>
#include <d3d11_4.h>

class InputLayout
{
private:
	std::vector<std::string> semanticNames; // Needed to store the semantic names of the element descs
	std::vector<D3D11_INPUT_ELEMENT_DESC> elements;
	ID3D11InputLayout* inputLayout = nullptr;

public:
	// =delete gör att de operatona är omöjliga och ska inte gå att göra eller köra
	InputLayout() = default;
	~InputLayout();
	InputLayout(const InputLayout& other) = delete;
	InputLayout& operator=(const InputLayout& other) = delete;
	InputLayout(InputLayout&& other) = delete;
	InputLayout& operator=(InputLayout&& other) = delete;

	void AddInputElement(const std::string& semanticName, DXGI_FORMAT format);
	void FinalizeInputLayout(ID3D11Device* device, const void* vsDataPtr, size_t vsDataSize);

	ID3D11InputLayout* GetInputLayout() const;
};

