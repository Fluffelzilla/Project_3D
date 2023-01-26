#include "Mesh.h"

void Mesh::Initialize(ID3D11Device* device, const MeshData& meshInfo)
{
	MeshData data;
	data.subMeshInfo = meshInfo.subMeshInfo;
	data.indexInfo = meshInfo.indexInfo;
	data.vertexInfo = meshInfo.vertexInfo;

	vertexBuffer.Initialize(device, data.vertexInfo.sizeOfVertex, data.vertexInfo.nrOfVerticesInBuffer,data.vertexInfo.vertexData);
	indexBuffer.Initialize(device, data.indexInfo.nrOfIndicesInBuffer, data.indexInfo.indexData);
}

void Mesh::BindMeshBuffers(ID3D11DeviceContext* context) const
{
}

void Mesh::PerformSubMeshDrawCall(ID3D11DeviceContext* context, size_t subMeshIndex) const
{
	subMeshes[subMeshIndex].PerformDrawCall(context);
}

size_t Mesh::GetNrOfSubMeshes() const
{
	//TODO: är troligen fel inmatat... fíxa rätt retur värde!!!
	return sizeof(subMeshes);
}

ID3D11ShaderResourceView* Mesh::GetAmbientSRV(size_t subMeshIndex) const
{
	return subMeshes[subMeshIndex].GetAmbientSRV();
}

ID3D11ShaderResourceView* Mesh::GetDiffuseSRV(size_t subMeshIndex) const
{
	return subMeshes[subMeshIndex].GetDiffuseSRV();
}

ID3D11ShaderResourceView* Mesh::GetSpecularSRV(size_t subMeshIndex) const
{
	return 	subMeshes[subMeshIndex].GetSpecularSRV();
}
