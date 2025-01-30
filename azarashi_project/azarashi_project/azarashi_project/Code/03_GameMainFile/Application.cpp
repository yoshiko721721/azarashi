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

Application* Application::m_Instance;		//�C���X�^���X

Sound sound;

int stagePage = 0;
int stageCount = 0;

Application::Application()
{

}

void Application::Init(HWND hWnd)
{
	m_Instance = new Application;
	D3D_Create(hWnd);							//DirectX��������
	sound.Init();
	srand((unsigned)time(NULL));
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::cerr << "SDL�̏������Ɏ��s���܂����BSDL_Error: " << SDL_GetError() << std::endl;
		return;
	}

	InitializeController();
	SDL_Joystick* joystick = SDL_JoystickOpen(0);
	//SDL_GameController* controller = SDL_GameControllerOpen(0);
	//�����V�[�����Z�b�g
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
	D3D_StartRender();		//�`��J�n

	m_Instance->m_Scene->Draw();

	D3D_FinishRender();		//�`��I��
}

void Application::Uninit(void)
{

	m_Instance->m_Scene->Uninit();
	sound.Uninit();
	D3D_Release();			//DirectX���I��
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
	//m_Scene�̒��g��nullptr���ᖳ���Ȃ�
	if (m_Instance->m_Scene != nullptr) {
		delete m_Instance->m_Scene;
		m_Instance->m_Scene = nullptr;
	}

	switch(sName)
	{
		case TITLESCENE:
			m_Instance->m_Scene = new TitleScene(false); // ���������m��
			m_Scene->Init();
			break;
		case LOADSCENE:
			m_Instance->m_Scene = new LoadScene; // ���������m��
			m_Instance->m_Scene->Init();
			break;
		case SELECTSCENE:
			m_Instance->m_Scene = new SelectScene; // ���������m��
			m_Instance->m_Scene->Init();
			break;
		/*case STAGESELECTSCENE:
			m_Instance->m_Scene = new StageSelectScene; // ���������m��
			m_Scene->Init();
			break;*/
		case GAMESCENE:
			m_Instance->m_Scene = new GameScene; // ���������m��
			m_Instance->m_Scene->Init();
			break;
		case STAGESCENE:
		{
			std::vector<ID3D11ShaderResourceView*> textures; // �K�؂ȃe�N�X�`���̏��������s��
			switch (stagePage)
			{
			case 0:
				if (stageCount == 0)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 1)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 2)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 3)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				break;
			case 1:
				if (stageCount == 0)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 1)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 2)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 3)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				break;
			case 2:
				if (stageCount == 0)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 1)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 2)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 3)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				break;
			case 3:
				if (stageCount == 0)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 1)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 2)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
				}
				else if (stageCount == 3)
				{
					m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
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
			std::vector<ID3D11ShaderResourceView*> textures; // �K�؂ȃe�N�X�`���̏��������s��
			m_Instance->m_Scene = new Stage1_1Scene(textures); // ���������m��
			m_Instance->m_Scene->Init();
			break;
		}
		case TESTSCENE02:
		{
			std::vector<ID3D11ShaderResourceView*> textures2;
			m_Instance->m_Scene = new TestScene_You(textures2); // ���������m��
			m_Scene->Init();
			break;
		}
		case TESTSCENE03:
		{
			std::vector<ID3D11ShaderResourceView*> textures; // �K�؂ȃe�N�X�`���̏��������s��
			m_Instance->m_Scene = new TestSceneNishiguchi(textures); // ���������m��
			m_Instance->m_Scene->Init();
			break;
		}
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
