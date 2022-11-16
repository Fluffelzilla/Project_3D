#include "constantBuffer.h"

ConstantBuffer::ConstantBuffer(ID3D11Device* device, size_t byteSize, void* initialData)
{
	bufferSize = byteSize;
	Initialize(device, byteSize, initialData);
}

ConstantBuffer::~ConstantBuffer()
{
	if (buffer)
	{
		buffer->Release();
		buffer = 0;
	}
}

void ConstantBuffer::Initialize(ID3D11Device* device, size_t byteSize, void* initialData)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = byteSize;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = initialData;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	device->CreateBuffer(&bufferDesc, &data, &buffer);
}

size_t ConstantBuffer::GetSize() const
{
	return bufferSize;
}

ID3D11Buffer* ConstantBuffer::GetBuffer() const
{
	return buffer;
}

void ConstantBuffer::UpdateBuffer(ID3D11DeviceContext* context, void* data)
{
	data.xOffset = 0.0f;
	data.yOffset = 0.5f;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	CopyMemory(mappedResource.pData, &data, sizeof(constBufferVertexShader));
	context->Unmap(buffer, 0);
	context->VSSetConstantBuffers(0, 1, &buffer);

}
