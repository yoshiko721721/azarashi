#include "textureManager.h"
#include "../05_WICTextureLoader/WICTextureLoader.h"

std::unordered_map<const wchar_t*, ID3D11ShaderResourceView*> TextureManager::list;

ID3D11ShaderResourceView* TextureManager::GetSRV(const wchar_t* imgname)
{
    auto pair = list.find(imgname);

    if (pair == list.end())
    {
        //�e�N�X�`���Ǎ���
        HRESULT hr = DirectX::CreateWICTextureFromFile(g_pDevice, imgname, NULL, &list[imgname]);
        if (FAILED(hr)) {
            MessageBoxA(NULL, "�e�N�X�`���Ǎ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
            return nullptr;
        }
    }

    return list[imgname];
}

TextureManager::~TextureManager()
{
    for (auto& texture : list)
    {
        texture.second->Release();
    }
}