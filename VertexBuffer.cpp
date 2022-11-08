#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(ID3D11Device* device, UINT sizeOfVertex, UINT nrOfVerticesInBuffer, void* vertexData)
{
	vertexSize = sizeOfVertex;
	nrOfVertices = nrOfVerticesInBuffer;

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexSize);
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertexData;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

}

VertexBuffer::~VertexBuffer()
{
	if (buffer)
	{
		buffer->Release();
		buffer = 0;
	}
}

void VertexBuffer::Initialize(ID3D11Device* device, UINT sizeOfVertex, UINT nrOfVerticesInBuffer, void* vertexData)
{
	
	device->CreateBuffer(&bufferDesc, &data, &vertexBuffer);
}

UINT VertexBuffer::GetNrOfVertices() const
{
    return nrOfVertices;
}

UINT VertexBuffer::GetVertexSize() const
{
    return vertexSize;
}

ID3D11Buffer* VertexBuffer::GetBuffer() const
{
    return buffer;
}

