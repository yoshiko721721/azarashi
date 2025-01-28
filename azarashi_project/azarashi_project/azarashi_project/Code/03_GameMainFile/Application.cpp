#include <time.h>
#include <math.h>
#include "Application.h"
#include "../01_Direct3D\Object.h"
#include "../02_Input/input.h"
#include "../03_GameMainFile/Game/GameScene.h"
#include "../03_GameMainFile/Title/TitleScene.h"
#include "../03_GameMainFile/StageSelectScene/StageSelectScene.h"
#include "Load/LoadScene.h"
#include "Select/SelectScene.h"
#include "Test/TestStageScene_Nakae.h"
#include "Game/Stage1-1Scene.h"
#include "Test/TestScene_You.h"
#include "../07_Camera/Camera.h"
#include "../06_Scene/TestSceneNishiguchi.h"
#include "StageSelectScene/StageSelectScene.h"

Application* Application::m_Instance;		//インスタンス

Sound sound;

int stagePage = 0;
int stageCount = 0;

Application::Application()
{

}

void Application::Init(HWND hWnd)
{
	m_Instance = new Application;
	D3D_Create(hWnd);							//DirectXを初期化
	sound.Init();
	srand((unsigned)time(NULL));
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::cerr << "SDLの初期化に失敗しました。SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}

	InitializeController();
	SDL_Joystick* joystick = SDL_JoystickOpen(0);
	//SDL_GameController* controller = SDL_GameControllerOpen(0);
	//初期シーンをセット
	m_Instance->m_Scene = new TitleScene(false);
	m_Instance->m_Scene->Init();

	Camera::Init();

}


void Application::Update(void)
{
	Input::Update();
	Camera::Update();
	m_Instance->m_Scene->Update();
}

void Application::Draw(void) {
	D3D_StartRender();		//描画開始

	m_Instance->m_Scene->Draw();

	D3D_FinishRender();		//描画終了
}

void Application::Uninit(void)
{

	m_Instance->m_Scene->Uninit();
	sound.Uninit();
	D3D_Release();			//DirectXを終了
}

Application* Application::GetInstance()
{
	return m_Instance;
}

Scene* Application::GetCurrentScene(void)
{
	return m_Scene;
}

void Application::ChangeScene(SceneList sName)
{
	//m_Sceneの中身がnullptrじゃ無いなら
	if (m_Instance->m_Scene != nullptr) {
		delete m_Instance->m_Scene;
		m_Instance->m_Scene = nullptr;
	}

	switch(sName)
	{
		case TITLESCENE:
			m_Instance->m_Scene = new TitleScene(false); // メモリを確保
			m_Scene->Init();
			break;
		case LOADSCENE:
			m_Instance->m_Scene = new LoadScene; // メモリを確保
			m_Instance->m_Scene->Init();
			break;
		case SELECTSCENE:
			m_Instance->m_Scene = new SelectScene; // メモリを確保
			m_Instance->m_Scene->Init();
			break;
		/*case STAGESELECTSCENE:
			m_Instance->m_Scene = new StageSelectScene; // メモリを確保
			m_Scene->Init();
			break;*/
		case GAMESCENE:
			m_Instance->m_Scene = new GameScene; // メモリを確保
			m_Instance->m_Scene->Init();
			break;
		case STAGESCENE:
		{
			std::vector<ID3D11ShaderResourceView*> textures; // 適切なテクスチャの初期化を行う
			switch (stagePage)
			{
			case 0:
				if (stageCount == 0)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 1)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 2)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 3)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				break;
			case 1:
				if (stageCount == 0)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 1)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 2)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 3)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				break;
			case 2:
				if (stageCount == 0)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 1)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 2)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 3)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				break;
			case 3:
				if (stageCount == 0)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 1)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 2)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				else if (stageCount == 3)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
				}
				break;
			default:
				break;
			}
					
			m_Instance->m_Scene->Init();
			break;
		}
		case TESTSCENE:
		{
			std::vector<ID3D11ShaderResourceView*> textures; // 適切なテクスチャの初期化を行う
			m_Instance->m_Scene = new Stage1_1Scene(textures); // メモリを確保
			m_Instance->m_Scene->Init();
			break;
		}
		case TESTSCENE02:
		{
			std::vector<ID3D11ShaderResourceView*> textures2;
			m_Instance->m_Scene = new TestScene_You(textures2); // メモリを確保
			m_Scene->Init();
			break;
		}
		case TESTSCENE03:
		{
			std::vector<ID3D11ShaderResourceView*> textures; // 適切なテクスチャの初期化を行う
			m_Instance->m_Scene = new TestSceneNishiguchi(textures); // メモリを確保
			m_Instance->m_Scene->Init();
			break;
		}
	}
}

void Application::DeleteObject(Object* pt)
{
	if (pt == NULL) return;

	pt->Uninit(); // 終了処理

	// 要素を削除
	m_Instance->m_Objects.erase(
		std::remove_if(
			m_Instance->m_Objects.begin(),
			m_Instance->m_Objects.end(),
			[pt](const std::unique_ptr<Object>& element) {return element.get() == pt; }),
		m_Instance->m_Objects.end());
	m_Instance->m_Objects.shrink_to_fit();
}

void Application::DeleteAllObject()
{
	// オブジェクト終了処理
	for (auto& o : m_Instance->m_Objects)
	{
		o->Uninit();
	}

	m_Instance->m_Objects.clear(); //全て削除
	m_Instance->m_Objects.shrink_to_fit();
}
