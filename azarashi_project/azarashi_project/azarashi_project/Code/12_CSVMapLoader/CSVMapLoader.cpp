#include "CSVMapLoader.h"
CSVMapLoader::~CSVMapLoader()
{

}

bool CSVMapLoader::FileOpen(std::string fileName)
{
    file.open(fileName); // クラスメンバーのfileを初期化 
    if (!file.is_open()) // ファイルが開けなかったらエラーメッセージを出す 
    {
        std::cerr << "ファイルを開けませんでした。" << std::endl; 
        return false;
    }
    return true;
}

void CSVMapLoader::FileClose()
{
    file.close();
}

void CSVMapLoader::CountRowsAndColumns()
{
    while (std::getline(file, line))
    {
        std::stringstream ss(line); std::string value; std::vector<int> row; // int型の値を格納するように変更 
        int currentColCount = 0; 
        while (std::getline(ss, value, ','))
        {
            row.push_back(std::stoi(value)); // 文字列をint型に変換 
            currentColCount++;
        } 
        if (currentColCount > colCount)
        {
            colCount = currentColCount; 
        }
        data.push_back(row); 
        rowCount++; 
    }
}

ID3D11ShaderResourceView* CSVMapLoader::LoadTexture(const wchar_t* filename)
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(g_pDevice, filename, NULL, &m_pTextureView);
    if (FAILED(hr))
    {
         MessageBoxA(NULL, "テクスチャ読み込み失敗", "エラー", MB_ICONERROR | MB_OK);
    }
    return m_pTextureView;
}

void CSVMapLoader::LoadTextures()
{
    std::cout << "Loading textures..." << std::endl;

    // texturesベクターのサイズをBlockType_MAXに設定 
    textures.resize(BlockType_MAX);

    if (textures.size() < BlockType_MAX) 
    {
        std::cerr << "Error: textures vector size is less than BlockType_MAX" << std::endl;
        return;
    }

    textures[PLAYER] = LoadTexture(L"asset/pic/Player.png");
    std::cout << "プレイヤー読み込めました" << std::endl;
    textures[FLOOR] = LoadTexture(L"asset/pic/block_kusa_02.png");
    std::cout << "床を読み込めました" << std::endl;
    textures[WALL] = LoadTexture(L"asset/pic/block_bronze.png");
    std::cout << "壁読み込めました" << std::endl;
    textures[INCLINED_PLATFORM] = LoadTexture(L"asset/pic/InclinedPlatform.png");
    std::cout << "傾く足場読み込めました" << std::endl;
}

int CSVMapLoader::PrintValueAt(int row, int col)
{
    if (row < data.size() && col < data[row].size()) {
        int value = data[row][col];
        std::cout << "Value at [" << row << "][" << col << "]: " << value << std::endl;
    }
    else {
        std::cerr << "Error: Index out of range" << std::endl;
    }

    return data[row][col];
}


//中身の数字に沿ってUVでカットするのはどうだ(MapChipの話) 2024/12/18