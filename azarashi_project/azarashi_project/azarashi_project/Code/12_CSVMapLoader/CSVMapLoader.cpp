#include "CSVMapLoader.h"
CSVMapLoader::~CSVMapLoader()
{

}

bool CSVMapLoader::FileOpen(std::string fileName)
{
    file.open(fileName); // �N���X�����o�[��file�������� 
    if (!file.is_open()) // �t�@�C�����J���Ȃ�������G���[���b�Z�[�W���o�� 
    {
        std::cerr << "�t�@�C�����J���܂���ł����B" << std::endl; 
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
        std::stringstream ss(line); std::string value; std::vector<int> row; // int�^�̒l���i�[����悤�ɕύX 
        int currentColCount = 0; 
        while (std::getline(ss, value, ','))
        {
            row.push_back(std::stoi(value)); // �������int�^�ɕϊ� 
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
         MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
    }
    return m_pTextureView;
}

void CSVMapLoader::LoadTextures()
{
    std::cout << "Loading textures..." << std::endl;

    // textures�x�N�^�[�̃T�C�Y��BlockType_MAX�ɐݒ� 
    textures.resize(BlockType_MAX);

    if (textures.size() < BlockType_MAX) 
    {
        std::cerr << "Error: textures vector size is less than BlockType_MAX" << std::endl;
        return;
    }

    textures[PLAYER] = LoadTexture(L"asset/pic/Player.png");
    std::cout << "�v���C���[�ǂݍ��߂܂���" << std::endl;
    textures[FLOOR] = LoadTexture(L"asset/pic/block_kusa_02.png");
    std::cout << "����ǂݍ��߂܂���" << std::endl;
    textures[WALL] = LoadTexture(L"asset/pic/block_bronze.png");
    std::cout << "�Ǔǂݍ��߂܂���" << std::endl;
    textures[INCLINED_PLATFORM] = LoadTexture(L"asset/pic/InclinedPlatform.png");
    std::cout << "�X������ǂݍ��߂܂���" << std::endl;
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


//���g�̐����ɉ�����UV�ŃJ�b�g����̂͂ǂ���(MapChip�̘b) 2024/12/18