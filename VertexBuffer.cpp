#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(ID3D11Device* device, UINT sizeOfVertex, UINT nrOfVerticesInBuffer, void* vertexData)
{
	vertexSize = sizeOfVertex;
	nrOfVertices = nrOfVerticesInBuffer;
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

