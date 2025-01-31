#include "CSVMapLoader.h"
CSVMapLoader::~CSVMapLoader()
{

}

//---------------------------------------------------
//�t�@�C�����J���֐�
//---------------------------------------------------
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

//---------------------------------------------------
//�t�@�C�������֐�
//---------------------------------------------------
void CSVMapLoader::FileClose()
{
    file.close();
}

//---------------------------------------------------
//�t�@�C�����̐��l��2�����z��Ɉڂ��֐�
//---------------------------------------------------
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

	stagewide = data[1][1];
	stagehigt = data[1][2];

}

//--------------------------------------------------------
//�摜�̃e�N�X�`�������[�h����֐�
//--------------------------------------------------------
ID3D11ShaderResourceView* CSVMapLoader::LoadTexture(const wchar_t* filename)
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(g_pDevice, filename, NULL, &m_pTextureView);
    if (FAILED(hr))
    {
         MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
    }
    return m_pTextureView;
}

//--------------------------------------------------------
//�X�e�[�W����ɕK�v�ȉ摜�̃e�N�X�`�������[�h����֐�
//--------------------------------------------------------
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

	textures[GOAL] = LoadTexture(L"asset/pic/Goal.PNG");
	std::cout << "�S�[����ǂݍ��߂܂���" << std::endl;

    textures[WALL] = LoadTexture(L"asset/pic/Wall.png");
    std::cout << "�Ǔǂݍ��߂܂���" << std::endl;

    textures[INCLINED_PLATFORM] = LoadTexture(L"asset/pic/Block_01.png");
    std::cout << "�X������ǂݍ��߂܂���" << std::endl;

	textures[FLAT_PLATFORM] = LoadTexture(L"asset/pic/Block_04.png");
	std::cout << "�X���Ȃ�����ǂݍ��߂܂���" << std::endl;

	/*textures[BREAK_PLATFORM] = LoadTexture(L"asset/pic/Block_03.png");
	std::cout << "����鏰��ǂݍ��߂܂���" << std::endl;

	textures[HEAYVMOVING_PLATFORM] = LoadTexture(L"asset/pic/Block_02.png");
	std::cout << "������(�d��)�ǂݍ��߂܂���" << std::endl;

	textures[LIGHTMOVING_PLATFORM] = LoadTexture(L"asset/pic/Block_05.png");
	std::cout << "������(�y��)�ǂݍ��߂܂���" << std::endl;*/

	/*textures[OBSTACLE_ITEM] = LoadTexture(L"asset/pic/Ojama.png");
	std::cout << "���ז��A�C�e����ǂݍ��߂܂���" << std::endl;*/

	/*textures[ROUND_ROCK] = LoadTexture(L"asset/pic/block_bronze.png");
	std::cout << "�ۂ����ǂݍ��݂܂���" << std::endl;

	textures[SQUARE_ROCK] = LoadTexture(L"asset/pic/InclinedPlatform.png");
	std::cout << "�l�p�����ǂݍ��݂܂���" << std::endl;*/

	FloorBlockTextures[9]  = LoadTexture(L"asset/pic/Floor_09.png");
	FloorBlockTextures[11] = LoadTexture(L"asset/pic/Floor_11.png");

	WallBlockTextures[9]   = LoadTexture(L"asset/pic/Wall_09.png");
	WallBlockTextures[6] = LoadTexture(L"asset/pic/Wall_06.png");
	WallBlockTextures[12] = LoadTexture(L"asset/pic/Wall_12.png");

	inclined_PlatformTextures[1] = LoadTexture(L"asset/pic/Block_01.png");  //�X�����̊e�p�[�c(2�}�X)�@
	inclined_PlatformTextures[2] = LoadTexture(L"asset/pic/Block/Block_01/Block_01_02.png");  //�X�����̊e�p�[�c(2�}�X)�@
	inclined_PlatformTextures[3] = LoadTexture(L"asset/pic/Block/Block_01/Block_01_03.png");  //�X�����̊e�p�[�c(3�}�X)
	inclined_PlatformTextures[4] = LoadTexture(L"asset/pic/Block/Block_01/Block_01_04.png");  //�X�����̊e�p�[�c(4�}�X)
	inclined_PlatformTextures[5] = LoadTexture(L"asset/pic/Block/Block_01/Block_01_05.png");  //�X�����̊e�p�[�c(5�}�X)

	Flat_PlatformTextures[1] = LoadTexture(L"asset/pic/Block_04.png");  //�X���Ȃ����̊e�p�[�c(2�}�X)
	Flat_PlatformTextures[2] = LoadTexture(L"asset/pic/Block/Block_04/Block_04_02.png");  //�X���Ȃ����̊e�p�[�c(2�}�X)
	Flat_PlatformTextures[3] = LoadTexture(L"asset/pic/Block/Block_04/Block_04_03.png");  //�X���Ȃ����̊e�p�[�c(3�}�X)
	Flat_PlatformTextures[4] = LoadTexture(L"asset/pic/Block/Block_04/Block_04_04.png");  //�X���Ȃ����̊e�p�[�c(4�}�X)
	Flat_PlatformTextures[5] = LoadTexture(L"asset/pic/Block/Block_04/Block_04_05.png");  //�X���Ȃ����̊e�p�[�c(5�}�X)
}

//--------------------------------------------------------
//�X�e�[�W�̉���������Ă���֐�
//--------------------------------------------------------
void CSVMapLoader::SetStageWidth()
{
	stagewide = data[2][1];
}

//--------------------------------------------------------
//�X�e�[�W�̏c��������Ă���֐�
//--------------------------------------------------------
void CSVMapLoader::SetStageHeight()
{
	stagehigt = data[1][1];
}

//--------------------------------------------------------
//�X�e�[�W�̏c��������Ă���֐�
//--------------------------------------------------------
void CSVMapLoader::CalculateStageCenter()
{
	startX = colCount * 128 / 2 - 64;	//X���̃X�^�[�g���_
	startY = rowCount * 128 / 2 - 64;	//Y���̃X�^�[�g�n�_
}

//--------------------------------------------------------
//�X�e�[�W�ɃI�u�W�F�N�g����ׂĂ����֐�
//--------------------------------------------------------
GamePointer* CSVMapLoader::AddObject(std::vector<std::unique_ptr<Object>>* m_MySceneObjects)
{
	GamePointer* p_player = nullptr;
	CalculateStageCenter();
	bool fastWall = true;
	bool fastFloor = true;
	int count = 0;//�m�F�p
	float x = -startX;//�ǂ�����X�^�[�g���邩�ǂ���(�ύX�\������)
	float y = -startY;//�ǂ�����X�^�[�g���邩�ǂ���(�ύX�\������)
	for (int i = rowCount - 1; i > -1; i--)//CSV�ɓ����Ă���}�X����
	{
		for (int j = 0; j < colCount; j++)
		{
			switch (data[i][j])
			{
			case NULLSPACE://�Ȃɂ��Ȃ��Ȃ�
			{
				//count++;
				break;
			}
			case FLOOR://���Ȃ�
			{
				int k = 1;
				while (data[i][j] == data[i][j + k])
				{
					data[i][j + k] = 0;
					k++;
				}

				auto newChip = Application::GetInstance()->AddObject<TestFloor>(x + 128 * (k / 2), y, BLOCKSIZE * k, BLOCKSIZE, 0, 0);//m
				newChip->SetTexture(FloorBlockTextures[k]);//�e�N�X�`����Set����
				newChip->Init();//������
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}
			case WALL://�ǂȂ�
			{
				int k = 1;
				while (data[i][j] == data[i - k][j])
				{
					data[i - k][j] = 0;
					k++;
					if (i - k == -1)
					{
						break;
					}
				}

				auto newChip = Application::GetInstance()->AddObject<TestWall>(x, y + 128 * (k /2) -64 , BLOCKSIZE, BLOCKSIZE * k,0,0);//�ǂ𐶐�
				newChip->SetTexture(WallBlockTextures[k]);//texture���Z�b�g
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				//count++;
				break;
			}
			case PLAYER://�v���C���[�Ȃ�
			{
				auto newChip = Application::GetInstance()->AddObject<GamePointer>(x, y, BLOCKSIZE, BLOCKSIZE);
				//newChip->SetTexture(textures[data[i][j]]);//texture���Z�b�g
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//�v���C���[�̂ݕ������܂�
				p_player = newChip;
				//x += 64
				//count++;
				break;
			}
			case GOAL:
			{
				auto newChip = Application::GetInstance()->AddObject<Goal>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);//texture���Z�b�g
				newChip->SetPos(x, y, 0);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//�v���C���[�̂ݕ������܂�
				break;
			}
			case INCLINED_PLATFORM://�X�����Ȃ�
			{
				int k = 1;
				while (data[i][j] == data[i][j + k])
				{
					data[i][j + k] = 0;
					k++;

				}
				int l;

				/*if (x <= -1)
				{
					l = -2;
				}
				else if (x >= 0)
				{
					l = 2;
				}*/

				auto newChip = Application::GetInstance()->AddObject<GameBlock>(x + 128 * (k / 2), y, BLOCKSIZE * k, BLOCKSIZE);
				newChip->SetTexture(inclined_PlatformTextures[k]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				
				//x += 64;
				//count++;
				break;
			}
			case FLAT_PLATFORM:
			{
				int k = 1;
				while (data[i][j] == data[i][j + k])
				{
					data[i][j + k] = 0;
					k++;

				}

				auto newChip = Application::GetInstance()->AddObject<GameBlock_stop>(x + 128 * (k / 2), y, BLOCKSIZE * k, BLOCKSIZE);
				newChip->SetTexture(inclined_PlatformTextures[k]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				//count++;
				break;
			}
			case BREAK_PLATFORM:
			{
				auto newChip = Application::GetInstance()->AddObject<BreakBlock>(x, y, BLOCKSIZE, BLOCKSIZE, stagewide, stagehigt);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				//count++;
				break;
			}
			case HEAYVMOVING_PLATFORM://������(�d��)�Ȃ�
			{
				auto newChip = Application::GetInstance()->AddObject<MoveGameBlock>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				//count++;
				break;
			}
			case LIGHTMOVING_PLATFORM://������(�y��)�Ȃ�
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
		y += BLOCKSIZE;
		x  = -startX;
	}

	return p_player;
}

//���g�̐����ɉ�����UV�ŃJ�b�g����̂͂ǂ���(MapChip�̘b) 2024/12/18