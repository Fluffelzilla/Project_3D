#include "ShaderResourceTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

ShaderResourceTexture::ShaderResourceTexture(ID3D11Device* device, UINT width, UINT height, void* textureData)
{
    Initialize(device, width, height, textureData);
}

ShaderResourceTexture::ShaderResourceTexture(ID3D11Device* device, const char* pathToTextureFile)
{
    Initialize(device, pathToTextureFile);
}

ShaderResourceTexture::~ShaderResourceTexture()
{
    if (srv!=nullptr)
    {
        srv->Release();
        srv = 0;
    }
    if (texture!=0)
    {
        texture->Release();
        texture = 0;
    }
}

void ShaderResourceTexture::Initialize(ID3D11Device* device, UINT width, UINT height, void* textureData)
{
    //TODO: kolla om hanteringen av textureDesc och Data är rätt!!!
    D3D11_TEXTURE2D_DESC textureDesc;
    textureDesc.Width = width;
    textureDesc.Height = height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA data;
    data.pSysMem = textureData;
    data.SysMemPitch = 0;
    data.SysMemSlicePitch = 0;

    device->CreateTexture2D(&textureDesc, &data, &texture);

    //hittat på microsofts dokumentation
    //D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
    //memset(&SRVDesc, 0, sizeof(SRVDesc));
    //SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    //SRVDesc.Texture2D.MipLevels = 1;

    //TODO: ska det vara nullptr nedan eller ska SRVDesc användas?
    device->CreateShaderResourceView(texture, nullptr, &srv);

}

void ShaderResourceTexture::Initialize(ID3D11Device* device, const char* pathToTextureFile)
{
    int w; //whith
    int h; //height
    int c; //channels
    unsigned char* pData;
    pData = stbi_load(pathToTextureFile, &w, &h, &c, 0);
    
    D3D11_TEXTURE2D_DESC textureDesc;
    textureDesc.Width = w;
    textureDesc.Height = h;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA data;
    data.pSysMem = pData; 
    data.SysMemPitch = w * 4;
    data.SysMemSlicePitch = w * h * 4;

    device->CreateTexture2D(&textureDesc, &data, &texture);
    device->CreateShaderResourceView(texture, nullptr, &srv);
}

ID3D11ShaderResourceView* ShaderResourceTexture::GetSRV() const
{
    return srv;
}
