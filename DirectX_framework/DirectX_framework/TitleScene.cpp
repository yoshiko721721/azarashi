#include "TitleScene.h"
//------------------------------
//Title�V�[�����̂�Init�`Uninit
//------------------------------
void TitleScene::Init()
{
    // ����������
    TitleBackground.Init();
    TitleCamera.Init();
}

void TitleScene::Update()
{
    // �X�V����
    TitleBackground.Update();
    TitleCamera.Update();
}

void TitleScene::Draw()
{
    // �`�揈��
    D3D_StartRender();  //�`��J�n
    TitleBackground.Draw(&TitleCamera);
    D3D_FinishRender(); //�`��I��
}

void TitleScene::Uninit()
{
    //�I������
    TitleBackground.Uninit();
    //input.Uninit();
    //D3D_Release();//DirectX���I��
}
