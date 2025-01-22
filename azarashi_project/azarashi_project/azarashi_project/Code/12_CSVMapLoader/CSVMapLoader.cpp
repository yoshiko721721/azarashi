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
	textures[NULLSPACE] = LoadTexture(L"asset/pic/empty.png");
	std::cout << "�����Ȃ��ǂݍ��߂܂���" << std::endl;

    textures[PLAYER] = LoadTexture(L"asset/pic/azarasi.png");
    std::cout << "�v���C���[�ǂݍ��߂܂���" << std::endl;

    textures[FLOOR] = LoadTexture(L"asset/pic/Floor.png");
    std::cout << "����ǂݍ��߂܂���" << std::endl;

    textures[WALL] = LoadTexture(L"asset/pic/Wall.png");
    std::cout << "�Ǔǂݍ��߂܂���" << std::endl;

    textures[INCLINED_PLATFORM] = LoadTexture(L"asset/pic/Block_01.png");
    std::cout << "�X������ǂݍ��߂܂���" << std::endl;

	textures[FLAT_PLATFORM] = LoadTexture(L"asset/pic/Block_04.png");
	std::cout << "�X���Ȃ�����ǂݍ��߂܂���" << std::endl;

	textures[BREAK_PLATFORM] = LoadTexture(L"asset/pic/Block_03.png");
	std::cout << "����鏰��ǂݍ��߂܂���" << std::endl;

	textures[HEAYVMOVING_PLATFORM] = LoadTexture(L"asset/pic/Block_02.png");
	std::cout << "������(�d��)�ǂݍ��߂܂���" << std::endl;

	textures[LIGHTMOVING_PLATFORM] = LoadTexture(L"asset/pic/Block_05.png");
	std::cout << "������(�y��)�ǂݍ��߂܂���" << std::endl;

	textures[OBSTACLE_ITEM] = LoadTexture(L"asset/pic/Ojama.png");
	std::cout << "���ז��A�C�e����ǂݍ��߂܂���" << std::endl;

	/*textures[ROUND_ROCK] = LoadTexture(L"asset/pic/block_bronze.png");
	std::cout << "�ۂ����ǂݍ��݂܂���" << std::endl;

	textures[SQUARE_ROCK] = LoadTexture(L"asset/pic/InclinedPlatform.png");
	std::cout << "�l�p�����ǂݍ��݂܂���" << std::endl;*/
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
	//128*128�Ȃ̂ŏc��MAX8�}�X����MAX15�}�X
	int Platformcount = 1;//�ǂ��Ȃ���͉��}�X�q�����Ă�����Ă���̂��𒲂ׂ�
	int count = 0;//�m�F�p
	float x = SCREEN_WIDTH * -1 / 2 + BLOCKSIZE / 2;//�ǂ�����X�^�[�g���邩�ǂ���(�ύX�\������)
	float y = SCREEN_HEIGHT / 2 - BLOCKSIZE / 2;//�ǂ�����X�^�[�g���邩�ǂ���(�ύX�\������)
	for (int i = 0; i < rowCount; i++)//CSV�ɓ����Ă���}�X���񂷂񂾂�
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
				auto newChip = Application::GetInstance()->AddObject<TestFloor>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}
			case WALL:
			{
				auto newChip = Application::GetInstance()->AddObject<TestWall>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}
			case PLAYER:
			{
				auto newChip = Application::GetInstance()->AddObject<GamePointer>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}
			case INCLINED_PLATFORM:
			{
				auto newChip = Application::GetInstance()->AddObject<GameBlock>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}
			/*case FLAT_PLATFORM:
			{
				auto newChip = Application::GetInstance()->AddObject<TestWall>(x, y, 64, 64);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}*/
			/*case BREAK_PLATFORM:
			{
				auto newChip = Application::GetInstance()->AddObject<TestWall>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}*/
			case HEAYVMOVING_PLATFORM:
			{
				auto newChip = Application::GetInstance()->AddObject<MoveGameBlock>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}
			case LIGHTMOVING_PLATFORM:
			{
				auto newChip = Application::GetInstance()->AddObject<MoveGameBlock>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}
			/*case OBSTACLE_ITEM:
			{
				auto newChip = Application::GetInstance()->AddObject<Snowman>(x, y, 64, 64);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}*/
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
			x += BLOCKSIZE;
		}
		y -= BLOCKSIZE;
		x = SCREEN_WIDTH * -1 / 2 + BLOCKSIZE / 2;
	}

}

//���g�̐����ɉ�����UV�ŃJ�b�g����̂͂ǂ���(MapChip�̘b) 2024/12/18