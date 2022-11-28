#include "SubMesh.h"

void SubMesh::Initialize(size_t startIndexValue, size_t nrOfIndicesInSubMesh, ID3D11ShaderResourceView* ambientTextureSRV, ID3D11ShaderResourceView* diffuseTextureSRV, ID3D11ShaderResourceView* specularTextureSRV)
{
}

void SubMesh::PerformDrawCall(ID3D11DeviceContext* context) const
{
}

ID3D11ShaderResourceView* SubMesh::GetAmbientSRV() const
{
    return ambientTexture;
}

ID3D11ShaderResourceView* SubMesh::GetDiffuseSRV() const
{
    return diffuseTexture;
}

ID3D11ShaderResourceView* SubMesh::GetSpecularSRV() const
{
    return specularTexture;
}
