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

    textures[PLAYER] = LoadTexture(L"asset/pic/azarasi.png");
    std::cout << "�v���C���[�ǂݍ��߂܂���" << std::endl;
    textures[FLOOR] = LoadTexture(L"asset/pic/block_koori.png");
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

void CSVMapLoader::AddObject(std::vector<std::unique_ptr<Object>>* m_MySceneObjects)
{
	int Platformcount = 1;
	int count = 0;
	float x = SCREEN_WIDTH * -1 / 2 + 32;
	float y = SCREEN_HEIGHT / 2 - 32;
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			switch (data[i][j])
			{
			case NULLSPACE:
			{
				count++;
				break;
			}
			case FLOOR:
			{
				auto newChip = Application::GetInstance()->AddObject<TestFloor>(x, y, 64, 64);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}
			case WALL:
			{
				auto newChip = Application::GetInstance()->AddObject<TestWall>(x, y, 64, 64);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}
			case PLAYER:
			{
				/*auto newChip = Application::GetInstance()->AddObject<GamePointer>(x, y, 64, 64);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;*/
				count++;
				break;
			}
			default:
				break;
			}
			/*if (data[i][j] == NULLSPACE)
			{
				count++;
			}
			if (data[i][j] == FLOOR)
			{
				auto newChip = std::make_unique<GamePointer>(x, y, 100, 100);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				//m_MySceneObjects.push_back(std::move(newChip));
				m_MySceneObjects->emplace_back(Application::GetInstance()->AddObject<GamePointer>());
				count++;

				auto newChip = Application::GetInstance()->AddObject<TestFloor>(x, y, 64, 64);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				count++;
				//x += 64;
			}
			if (data[i][j] == WALL)
			{
				auto newChip = Application::GetInstance()->AddObject<TestWall>(x, y, 64, 64);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
			}
			if (data[i][j] == PLAYER)
			{
				auto newChip = Application::GetInstance()->AddObject<GamePointer>(x, y, 64, 64);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
			}
			/*if (data[i][j] == INCLINED_PLATFORM)
			{
				//for(csvMapLoader.data[i][j] ==)
				for (int k = 0; j + k >= colCount; k++)
				{
					if (data[i][j + k] == data[i][j])
					{
						Platformcount++;
					}
					else
					{
						auto newChip = Application::GetInstance()->AddObject<InclinedPlatform>(x, y, 64 * Platformcount, 64);
						newChip->SetTexture(textures[data[i][j]]);
						newChip->Init();
						m_MySceneObjects->emplace_back(newChip);

						break;
					}
				}

			}*/
			x += 64;
		}
		y -= 64;
		x = SCREEN_WIDTH * -1 / 2 + 32;
	}

}

//���g�̐����ɉ�����UV�ŃJ�b�g����̂͂ǂ���(MapChip�̘b) 2024/12/18