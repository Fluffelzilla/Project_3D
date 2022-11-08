#include "InputLayout.h"


InputLayout::~InputLayout()
{
	if (inputLayout)
	{
		inputLayout->Release();
		inputLayout = 0;
	}
}

void InputLayout::AddInputElement(const std::string& semanticName, DXGI_FORMAT format)
{
	//är detta korrekt?
	semanticNames.push_back(semanticName);
	//elements.push_back(D3D11_INPUT_ELEMENT_DESC({ semanticName.c_str(), 0, format, 0, 0 + 12 * elements.size(), D3D11_INPUT_PER_VERTEX_DATA, 0 }));
}

void InputLayout::FinalizeInputLayout(ID3D11Device* device, const void* vsDataPtr, size_t vsDataSize)
{
	//inputLayout = new InputLayout*(elements);
	//HRESULT hr = device->CreateInputLayout(elements, elements.size(), vsDataPtr, vsDataSize, &inputLayout);


	//är detta rätt???
	//hur gör jag detta???
}

ID3D11InputLayout* InputLayout::GetInputLayout() const
{
    return inputLayout;
}
