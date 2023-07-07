#include "Model.h"

Model::Model(std::wstring filePath)
{

}

void Model::render(ID3D11DeviceContext* immediateContext, ID3D11RenderTargetView* rtv,
    ID3D11DepthStencilView* dsView, D3D11_VIEWPORT& viewport, ID3D11InputLayout* inputLayout,
    ID3D11Buffer* vertexBuffer, ID3D11Buffer* cameraBuffer, Shader& vShader, Shader& pShader)
{
    UINT stride = sizeof(float) * 8;
    UINT offset = 0;
    immediateContext->VSSetConstantBuffers(0, 1, &cameraBuffer);
    immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    immediateContext->IASetInputLayout(inputLayout);
    immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    immediateContext->RSSetViewports(1, &viewport);
    immediateContext->OMSetRenderTargets(1, &rtv, dsView);
    vShader.BindShader(immediateContext);
    pShader.BindShader(immediateContext);

    immediateContext->Draw(/*NrOfVertices*/ 0, 0);
}

