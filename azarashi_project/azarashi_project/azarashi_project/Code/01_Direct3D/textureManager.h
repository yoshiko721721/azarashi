#pragma once
#include"direct3d.h"
#include<unordered_map>

class TextureManager
{
private:
	static std::unordered_map<const wchar_t*, ID3D11ShaderResourceView*> list;

public:
	static ID3D11ShaderResourceView* GetSRV(const wchar_t* imgname);

	~TextureManager();
};

