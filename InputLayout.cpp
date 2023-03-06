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

	semanticNames.push_back(semanticName);
	if (elements.size()<=0)
	{
		D3D11_INPUT_ELEMENT_DESC temp = { "", 0, format, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		elements.push_back(temp);
	}
	else
	{
		D3D11_INPUT_ELEMENT_DESC temp = { "", 0, format, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		elements.push_back(temp);
	}
}

void InputLayout::FinalizeInputLayout(ID3D11Device* device, const void* vsDataPtr, size_t vsDataSize)
{
	const int nrOfElements = 2;
	//for (unsigned int i = 0; i < elements.size(); i++)
	//{
	//	elements[i].SemanticName = semanticNames[i].c_str();
	//}
	//device->CreateInputLayout(elements.data(), elements.size(), vsDataPtr, vsDataSize, &inputLayout);

	D3D11_INPUT_ELEMENT_DESC inputDesc[nrOfElements] =
	{
		{"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{"COLOUR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12, D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	HRESULT hr = device->CreateInputLayout(inputDesc, nrOfElements, vsDataPtr, vsDataSize, &inputLayout);

}

ID3D11InputLayout* InputLayout::GetInputLayout() const
{
    return inputLayout;
}
