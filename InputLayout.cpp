#include "InputLayout.h"

InputLayout::InputLayout()
{
}

InputLayout::~InputLayout()
{
	if (inputLayout)
	{
		inputLayout->Release();
	}
}

void InputLayout::AddInputElement(const std::string& semanticName, DXGI_FORMAT format)
{
}

void InputLayout::FinalizeInputLayout(ID3D11Device* device, const void* vsDataPtr, size_t vsDataSize)
{
}

ID3D11InputLayout* InputLayout::GetInputLayout() const
{
    return nullptr;
}
