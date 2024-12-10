#include <time.h>
#include <math.h>
#include "Application.h"
#include "../01_Direct3D\Object.h"




Application::Application()
{
}

void Application::Init(HWND hWnd)
{

	D3D_Create(hWnd);							//DirectX��������
	srand((unsigned)time(NULL));
	//�����V�[�����Z�b�g
	sceneManager.ChangeScene(std::make_unique<TitleScene>());
}

void Application::Update(void)
{
	Input::Update();
	sceneManager.Update();
}

void Application::Draw(void) {
	D3D_StartRender();		//�`��J�n

	sceneManager.Draw();

	D3D_FinishRender();		//�`��I��
}

void Application::Uninit(void)
{

	sceneManager.Uninit();

	D3D_Release();			//DirectX���I��
}