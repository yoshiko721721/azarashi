#include <windows.h>
#include "SceneManager.h"
#include "Game.h"
//#include "TitleScene.h" // �����V�[���̃w�b�_�[���C���N���[�h

void Game::Init(HWND hWnd)
{
    // DirectX�̏�����
    D3D_Create(hWnd);
    // �����V�[���̐ݒ�
    sceneManager.ChangeScene(std::make_unique<TitleScene>());
}

void Game::Update()
{
    // �Q�[���S�̂̍X�V����
      input.Update();
 
    if (input.GetKeyPress(VK_Q))
    {
        sceneManager.ChangeScene(std::make_unique<GameScene>());
    }
    if (input.GetKeyPress(VK_E))
    {
        sceneManager.ChangeScene(std::make_unique<TitleScene>());
    }

    sceneManager.Update();//SceneManager��Update�Ɉړ����ăV�[�����̂��X�V����
}

void Game::Draw()
{
    // �Q�[���S�̂̕`�揈��
    sceneManager.Draw();
}

void Game::Uninit()
{
    // �Q�[���S�̂̏I������
    D3D_Release();
}

bool Game::ShouldExit()
{
    // �I�������̔���
    return 0;
}