#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(ID3D11Device* device, size_t nrOfIndicesInBuffer, uint32_t* indexData)
{
	nrOfIndices = nrOfIndicesInBuffer;
	Initialize(device, nrOfIndices, indexData);
}

IndexBuffer::~IndexBuffer()
{
	if (buffer)
	{
		buffer->Release();
		buffer = 0;
	}
}

void IndexBuffer::Initialize(ID3D11Device* device, size_t nrOfIndicesInBuffer, uint32_t* indexData)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = nrOfIndicesInBuffer * sizeof(indexData); // ska det vara index data?
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // kolla upp om det ska vara default istället
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = indexData; // kan vara fel, ska var indices.
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	device->CreateBuffer(&bufferDesc, &data, &buffer);
}

size_t IndexBuffer::GetNrOfIndices() const
{
	return sizeof(nrOfIndices);
}

ID3D11Buffer* IndexBuffer::GetBuffer() const
{
	return buffer;
}
