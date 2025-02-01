#include "CSVMapLoader.h"
CSVMapLoader::~CSVMapLoader()
{

}

//---------------------------------------------------
//ファイルを開く関数
//---------------------------------------------------
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

//---------------------------------------------------
//ファイルを閉じる関数
//---------------------------------------------------
void CSVMapLoader::FileClose()
{
    file.close();
}

//---------------------------------------------------
//ファイル内の数値を2次元配列に移す関数
//---------------------------------------------------
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

	stagewide = data[1][1];
	stagehigt = data[1][2];

}

//--------------------------------------------------------
//画像のテクスチャをロードする関数
//--------------------------------------------------------
ID3D11ShaderResourceView* CSVMapLoader::LoadTexture(const wchar_t* filename)
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(g_pDevice, filename, NULL, &m_pTextureView);
    if (FAILED(hr))
    {
         MessageBoxA(NULL, "テクスチャ読み込み失敗", "エラー", MB_ICONERROR | MB_OK);
    }
    return m_pTextureView;
}

//--------------------------------------------------------
//ステージ製作に必要な画像のテクスチャをロードする関数
//--------------------------------------------------------
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

	textures[GOAL] = LoadTexture(L"asset/pic/Goal.PNG");
	std::cout << "ゴールを読み込めました" << std::endl;

    textures[WALL] = LoadTexture(L"asset/pic/Wall.png");
    std::cout << "壁読み込めました" << std::endl;

    textures[INCLINED_PLATFORM] = LoadTexture(L"asset/pic/Block_01.png");
    std::cout << "傾く足場読み込めました" << std::endl;

	textures[FLAT_PLATFORM] = LoadTexture(L"asset/pic/Block_04.png");
	std::cout << "傾かない足場読み込めました" << std::endl;

	/*textures[BREAK_PLATFORM] = LoadTexture(L"asset/pic/Block_03.png");
	std::cout << "崩れる床を読み込めました" << std::endl;

	textures[HEAYVMOVING_PLATFORM] = LoadTexture(L"asset/pic/Block_02.png");
	std::cout << "動く床(重い)読み込めました" << std::endl;

	textures[LIGHTMOVING_PLATFORM] = LoadTexture(L"asset/pic/Block_05.png");
	std::cout << "動く床(軽い)読み込めました" << std::endl;*/

	/*textures[OBSTACLE_ITEM] = LoadTexture(L"asset/pic/Ojama.png");
	std::cout << "お邪魔アイテムを読み込めました" << std::endl;*/

	/*textures[ROUND_ROCK] = LoadTexture(L"asset/pic/block_bronze.png");
	std::cout << "丸い岩を読み込みました" << std::endl;

	textures[SQUARE_ROCK] = LoadTexture(L"asset/pic/InclinedPlatform.png");
	std::cout << "四角い岩を読み込みました" << std::endl;*/

	FloorBlockTextures[9]  = LoadTexture(L"asset/pic/Floor_09.png");
	FloorBlockTextures[11] = LoadTexture(L"asset/pic/Floor_11.png");

	WallBlockTextures[9]   = LoadTexture(L"asset/pic/Wall_09.png");
	WallBlockTextures[6] = LoadTexture(L"asset/pic/Wall_06.png");
	WallBlockTextures[12] = LoadTexture(L"asset/pic/Wall_12.png");

	inclined_PlatformTextures[1] = LoadTexture(L"asset/pic/Block_01.png");  //傾く床の各パーツ(2マス)　
	inclined_PlatformTextures[2] = LoadTexture(L"asset/pic/Block/Block_01/Block_01_02.png");  //傾く床の各パーツ(2マス)　
	inclined_PlatformTextures[3] = LoadTexture(L"asset/pic/Block/Block_01/Block_01_03.png");  //傾く床の各パーツ(3マス)
	inclined_PlatformTextures[4] = LoadTexture(L"asset/pic/Block/Block_01/Block_01_04.png");  //傾く床の各パーツ(4マス)
	inclined_PlatformTextures[5] = LoadTexture(L"asset/pic/Block/Block_01/Block_01_05.png");  //傾く床の各パーツ(5マス)

	Flat_PlatformTextures[1] = LoadTexture(L"asset/pic/Block_04.png");  //傾かない床の各パーツ(2マス)
	Flat_PlatformTextures[2] = LoadTexture(L"asset/pic/Block/Block_04/Block_04_02.png");  //傾かない床の各パーツ(2マス)
	Flat_PlatformTextures[3] = LoadTexture(L"asset/pic/Block/Block_04/Block_04_03.png");  //傾かない床の各パーツ(3マス)
	Flat_PlatformTextures[4] = LoadTexture(L"asset/pic/Block/Block_04/Block_04_04.png");  //傾かない床の各パーツ(4マス)
	Flat_PlatformTextures[5] = LoadTexture(L"asset/pic/Block/Block_04/Block_04_05.png");  //傾かない床の各パーツ(5マス)
}

//--------------------------------------------------------
//ステージの横幅を取ってくる関数
//--------------------------------------------------------
void CSVMapLoader::SetStageWidth()
{
	stagewide = data[2][1];
}

//--------------------------------------------------------
//ステージの縦幅を取ってくる関数
//--------------------------------------------------------
void CSVMapLoader::SetStageHeight()
{
	stagehigt = data[1][1];
}

//--------------------------------------------------------
//ステージの縦幅を取ってくる関数
//--------------------------------------------------------
void CSVMapLoader::CalculateStageCenter()
{
	startX = colCount * 128 / 2 - 64;	//X軸のスタート時点
	startY = rowCount * 128 / 2 - 64;	//Y軸のスタート地点
}

//--------------------------------------------------------
//ステージにオブジェクトを並べていく関数
//--------------------------------------------------------
GamePointer* CSVMapLoader::AddObject(std::vector<std::unique_ptr<Object>>* m_MySceneObjects)
{
	GamePointer* p_player = nullptr;
	CalculateStageCenter();
	bool fastWall = true;
	bool fastFloor = true;
	int count = 0;//確認用
	float x = -startX;//どこからスタートするかどうか(変更可能性高め)
	float y = -startY;//どこからスタートするかどうか(変更可能性高め)
	for (int i = rowCount - 1; i > -1; i--)//CSVに入っているマス分回す
	{
		for (int j = 0; j < colCount; j++)
		{
			switch (data[i][j])
			{
			case NULLSPACE://なにもないなら
			{
				//count++;
				break;
			}
			case FLOOR://床なら
			{
				int k = 1;
				while (data[i][j] == data[i][j + k])
				{
					data[i][j + k] = 0;
					k++;
				}

				auto newChip = Application::GetInstance()->AddObject<TestFloor>(x + 128 * (k / 2), y, BLOCKSIZE * k, BLOCKSIZE, 0, 0);//m
				newChip->SetTexture(FloorBlockTextures[k]);//テクスチャをSetする
				newChip->Init();//初期化
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				count++;
				break;
			}
			case WALL://壁なら
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

				auto newChip = Application::GetInstance()->AddObject<TestWall>(x, y + 128 * (k /2) -64 , BLOCKSIZE, BLOCKSIZE * k,0,0);//壁を生成
				newChip->SetTexture(WallBlockTextures[k]);//textureをセット
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				//count++;
				break;
			}
			case PLAYER://プレイヤーなら
			{
				auto newChip = Application::GetInstance()->AddObject<GamePointer>(x, y, BLOCKSIZE, BLOCKSIZE);
				//newChip->SetTexture(textures[data[i][j]]);//textureをセット
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//プレイヤーのみ複製します
				p_player = newChip;
				//x += 64
				//count++;
				break;
			}
			case GOAL:
			{
				auto newChip = Application::GetInstance()->AddObject<Goal>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);//textureをセット
				newChip->SetPos(x, y, 0);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//プレイヤーのみ複製します
				break;
			}
			case INCLINED_PLATFORM://傾く床なら
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
			case HEAYVMOVING_PLATFORM://動く床(重い)なら
			{
				auto newChip = Application::GetInstance()->AddObject<MoveGameBlock>(x, y, BLOCKSIZE, BLOCKSIZE);
				newChip->SetTexture(textures[data[i][j]]);
				newChip->Init();
				m_MySceneObjects->emplace_back(newChip);
				//x += 64;
				//count++;
				break;
			}
			case LIGHTMOVING_PLATFORM://動く床(軽い)なら
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

//中身の数字に沿ってUVでカットするのはどうだ(MapChipの話) 2024/12/18