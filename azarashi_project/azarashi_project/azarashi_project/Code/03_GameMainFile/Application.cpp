#include <time.h>
#include <math.h>
#include "Application.h"
#include "../01_Direct3D\Object.h"
#include "../02_Input/input.h"
#include "../03_GameMainFile/Game/GameScene.h"
#include "../03_GameMainFile/Title/TitleScene.h"



Application* Application::m_Instance;		//�C���X�^���X

Application::Application()
{
}

void Application::Init(HWND hWnd)
{

	m_Instance = new Application;
	D3D_Create(hWnd);							//DirectX��������
	srand((unsigned)time(NULL));
	//�����V�[�����Z�b�g
	m_Instance->m_Scene = new TitleScene;
}

void Application::Update(void)
{
	Input::Update();
	m_Instance->m_Scene->Update();
}

void Application::Draw(void) {
	D3D_StartRender();		//�`��J�n

	m_Instance->m_Scene->Draw();

	D3D_FinishRender();		//�`��I��
}

void Application::Uninit(void)
{

	m_Instance->m_Scene->Uninit();

	D3D_Release();			//DirectX���I��
}

Application* Application::GetInstance()
{
	return m_Instance;
}

void Application::ChangeScene(SceneList sName)
{
	//m_Scene�̒��g��nullptr���ᖳ���Ȃ�
	if (m_Instance->m_Scene != nullptr) {
		delete m_Instance->m_Scene;
		m_Instance->m_Scene = nullptr;
	}

	switch (sName)
	{
	case TITLESCENE:
		m_Instance->m_Scene = new TitleScene; // ���������m��
		break;
	case GAMESCENE:
		m_Instance->m_Scene = new GameScene; // ���������m��
		break;
	}

}

void Application::DeleteObject(Object* pt)
{
	if (pt == NULL) return;

	pt->Uninit(); // �I������

	// �v�f���폜
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
	// �I�u�W�F�N�g�I������
	for (auto& o : m_Instance->m_Objects)
	{
		o->Uninit();
	}

	m_Instance->m_Objects.clear(); //�S�č폜
	m_Instance->m_Objects.shrink_to_fit();
}
