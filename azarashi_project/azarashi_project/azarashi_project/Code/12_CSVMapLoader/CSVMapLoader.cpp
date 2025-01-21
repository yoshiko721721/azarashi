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
	textures[NULLSPACE] = LoadTexture(L"asset/pic/empty.png");
	std::cout << "何もない読み込めました" << std::endl;

    textures[PLAYER] = LoadTexture(L"asset/pic/azarasi.png");
    std::cout << "プレイヤー読み込めました" << std::endl;

    textures[FLOOR] = LoadTexture(L"asset/pic/Floor.png");
    std::cout << "床を読み込めました" << std::endl;

    textures[WALL] = LoadTexture(L"asset/pic/Wall.png");
    std::cout << "壁読み込めました" << std::endl;

    textures[INCLINED_PLATFORM] = LoadTexture(L"asset/pic/Block_01.png");
    std::cout << "傾く足場読み込めました" << std::endl;

	textures[FLAT_PLATFORM] = LoadTexture(L"asset/pic/Block_04.png");
	std::cout << "傾かない足場読み込めました" << std::endl;

	textures[BREAK_PLATFORM] = LoadTexture(L"asset/pic/Block_03.png");
	std::cout << "崩れる床を読み込めました" << std::endl;

	textures[HEAYVMOVING_PLATFORM] = LoadTexture(L"asset/pic/Block_02.png");
	std::cout << "動く床(重い)読み込めました" << std::endl;

	textures[LIGHTMOVING_PLATFORM] = LoadTexture(L"asset/pic/Block_05.png");
	std::cout << "動く床(軽い)読み込めました" << std::endl;

	textures[OBSTACLE_ITEM] = LoadTexture(L"asset/pic/Ojama.png");
	std::cout << "お邪魔アイテムを読み込めました" << std::endl;

	/*textures[ROUND_ROCK] = LoadTexture(L"asset/pic/block_bronze.png");
	std::cout << "丸い岩を読み込みました" << std::endl;

	textures[SQUARE_ROCK] = LoadTexture(L"asset/pic/InclinedPlatform.png");
	std::cout << "四角い岩を読み込みました" << std::endl;*/
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
	//128*128なので縦はMAX8マス横はMAX15マス
	int Platformcount = 1;//壁やらなんやらは何マス繋がっておかれているのかを調べる
	int count = 0;//確認用
	float x = SCREEN_WIDTH * -1 / 2 + BLOCKSIZE / 2;//どこからスタートするかどうか(変更可能性高め)
	float y = SCREEN_HEIGHT / 2 - BLOCKSIZE / 2;//どこからスタートするかどうか(変更可能性高め)
	for (int i = 0; i < rowCount; i++)//CSVに入っているマス分回すんだぜ
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

//中身の数字に沿ってUVでカットするのはどうだ(MapChipの話) 2024/12/18