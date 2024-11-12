#include "GameScene.h"
//------------------------------
//Game�V�[�����̂�Init�`Uninit
//------------------------------
void GameScene::Init()
{
    // ����������
    GameBackGround.Init();
    GamePointer.Init();
    GameBlock.Init();
}

void GameScene::Update()
{
    // �X�V����
    GameBackGround.Update();
    GamePointer.Update();
    GameBlock.Update();
    GameCamera.Update();
}

void GameScene::Draw()
{   // �`�揈��
    D3D_StartRender();  //�`��J�n
    GameBackGround.Draw(&GameCamera);
    GamePointer.Draw(&GameCamera);
    GameBlock.Draw(&GameCamera);
    D3D_FinishRender(); //�`��I��
}

void GameScene::Uninit()
{
    // �I������
    GameBackGround.Uninit();
    GamePointer.Uninit();
    GameBlock.Uninit();
    //D3D_Release();//DirectX���I��
}
