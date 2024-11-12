#include "GameCamera.h"
//=======================================
//����������
//=======================================
void GameCamera::Init()//2024/10/28
{
    // �����ʒu�Ɖ�]��ݒ�
    m_position = DirectX::XMFLOAT3(0.0f, 0.0f, -5.0f);
    m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

    // �r���[�s��Ǝˉe�s����X�V
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

//=======================================
//�X�V����
//=======================================
void GameCamera::Update()
{
    input.Update();
    DirectX::XMFLOAT3 pos = GetPosition();
    if (input.GetKeyPress(VK_RIGHT))
    {
        pos.x += 0.5f;
    }
    SetPosition(pos.x, pos.y, pos.z);
    //UpdateViewMatrix();
}

//=======================================
//�`�揈��
//=======================================
void GameCamera::Draw()
{


}

//=======================================
//�I������
//=======================================
void GameCamera::Uninit()
{


}


