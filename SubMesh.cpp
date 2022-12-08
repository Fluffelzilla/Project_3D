#include "SubMesh.h"

void SubMesh::Initialize(size_t startIndexValue, size_t nrOfIndicesInSubMesh, ID3D11ShaderResourceView* ambientTextureSRV, ID3D11ShaderResourceView* diffuseTextureSRV, ID3D11ShaderResourceView* specularTextureSRV)
{
    ambientTexture = ambientTextureSRV;
    diffuseTexture = diffuseTextureSRV;
    specularTexture = specularTextureSRV;
    startIndex = startIndexValue;
    nrOfIndices = nrOfIndicesInSubMesh;
}

void SubMesh::PerformDrawCall(ID3D11DeviceContext* context) const
{
    //saknas något att rita, som är beroende av vertex data?
    for (int i = 0; i < nrOfIndices; i++)
    {
        //context->Draw()
    }
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
