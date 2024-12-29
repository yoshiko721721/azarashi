#include <time.h>
#include <math.h>
#include "Application.h"
#include "../01_Direct3D\Object.h"
#include "../02_Input/input.h"
#include "../03_GameMainFile/Game/GameScene.h"
#include "../03_GameMainFile/Title/TitleScene.h"



Application* Application::m_Instance;		//インスタンス

Application::Application()
{
}

void Application::Init(HWND hWnd)
{

	m_Instance = new Application;
	D3D_Create(hWnd);							//DirectXを初期化
	srand((unsigned)time(NULL));
	//初期シーンをセット
	m_Instance->m_Scene = new TitleScene;
}

void Application::Update(void)
{
	Input::Update();
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

	D3D_Release();			//DirectXを終了
}

Application* Application::GetInstance()
{
	return m_Instance;
}

void Application::ChangeScene(SceneList sName)
{
	//m_Sceneの中身がnullptrじゃ無いなら
	if (m_Instance->m_Scene != nullptr) {
		delete m_Instance->m_Scene;
		m_Instance->m_Scene = nullptr;
	}

	switch (sName)
	{
	case TITLESCENE:
		m_Instance->m_Scene = new TitleScene; // メモリを確保
		break;
	case GAMESCENE:
		m_Instance->m_Scene = new GameScene; // メモリを確保
		break;
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
