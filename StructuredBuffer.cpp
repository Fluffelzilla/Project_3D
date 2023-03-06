#include "StructuredBuffer.h"

StructuredBuffer::StructuredBuffer(ID3D11Device* device, UINT sizeOfElement, size_t nrOfElementsInBuffer, void* bufferData, bool dynamic)
{
	Initialize(device, sizeOfElement, nrOfElementsInBuffer, bufferData, dynamic);
}

StructuredBuffer::~StructuredBuffer()
{
	if (buffer!=nullptr)
	{
		buffer->Release();
		buffer = 0;
	}
	if (srv!=nullptr)
	{
		srv->Release();
		srv = 0;
	}
}

void StructuredBuffer::Initialize(ID3D11Device* device, UINT sizeOfElement, size_t nrOfElementsInBuffer, void* bufferData, bool dynamic)
{
	//TODO: ska det vara buffer data? kolla upp om det ska vara default istället på usage!!!
	nrOfElements = nrOfElementsInBuffer;
	elementSize = sizeOfElement;
	
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = nrOfElements * elementSize;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	if (dynamic == true)
	{
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = 0;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
		bufferDesc.CPUAccessFlags = 0;
	}

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = bufferData;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	device->CreateBuffer(&bufferDesc, &data, &buffer);
	device->CreateShaderResourceView(buffer, nullptr, &srv);
}

void StructuredBuffer::UpdateBuffer(ID3D11DeviceContext* context, void* data)
{
	//TODO: kolla om min buffer ska sättas till vertex elr pixel shader elr båda. ska srv också sättas?
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	CopyMemory(mappedResource.pData, &data, sizeof(data));
	context->Unmap(buffer, 0);
	context->VSSetConstantBuffers(0, 1, &buffer);
	context->VSSetShaderResources(0, 1, &srv);
}

UINT StructuredBuffer::GetElementSize() const
{
	return elementSize;
}

size_t StructuredBuffer::GetNrOfElements() const
{
	return nrOfElements;
}

ID3D11ShaderResourceView* StructuredBuffer::GetSRV() const
{
	return srv;
}
