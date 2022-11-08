#include "InputLayout.h"
#include <cassert>

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
	//assert(format!=float3);
	semanticNames.push_back(semanticName);
	D3D11_INPUT_ELEMENT_DESC temp = { semanticName.c_str(), 0, format, 0, 0 + 12 * elements.size(), D3D11_INPUT_PER_VERTEX_DATA, 0 };
	//obs ej alltid 3 floats ökning!! kan vara två float3 och sedan en float2 ex. position = float3, normal = float3, uvCoord = float2, försök fixa matten så det går och ta bort assert
	elements.push_back(temp);
}

void InputLayout::FinalizeInputLayout(ID3D11Device* device, const void* vsDataPtr, size_t vsDataSize)
{
	//create input layout funktion är rätt, måste lista ut hur det implementeras på rätt sätt till min inputlayout...
	//kommer min inputlayout få rätt data på detta vis?
	device->CreateInputLayout(elements.data(), elements.size(), vsDataPtr, vsDataSize, &inputLayout);
}

ID3D11InputLayout* InputLayout::GetInputLayout() const
{
    return inputLayout;
}
