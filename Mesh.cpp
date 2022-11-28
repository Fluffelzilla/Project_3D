#include "Mesh.h"

void Mesh::Initialize(ID3D11Device* device, const MeshData& meshInfo)
{
}

void Mesh::BindMeshBuffers(ID3D11DeviceContext* context) const
{
}

void Mesh::PerformSubMeshDrawCall(ID3D11DeviceContext* context, size_t subMeshIndex) const
{
}

size_t Mesh::GetNrOfSubMeshes() const
{
	return size_t();
}

ID3D11ShaderResourceView* Mesh::GetAmbientSRV(size_t subMeshIndex) const
{
	return nullptr;
}

ID3D11ShaderResourceView* Mesh::GetDiffuseSRV(size_t subMeshIndex) const
{
	return nullptr;
}

ID3D11ShaderResourceView* Mesh::GetSpecularSRV(size_t subMeshIndex) const
{
	return nullptr;
}
