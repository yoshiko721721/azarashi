#include "TitleCamera.h"

//=======================================
//����������
//=======================================
void TitleCamera::Init()
{
    // �����ʒu�Ɖ�]��ݒ�
    m_position = DirectX::XMFLOAT3(2.0f, 0.0f, 0.0f);
    m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

    // �r���[�s��Ǝˉe�s����X�V
    UpdateViewMatrix();
    UpdateProjectionMatrix();

}

//=======================================
//�X�V����
//=======================================
void TitleCamera::Update()
{
    input.Update();
    DirectX::XMFLOAT3 pos = GetPosition();
    if (input.GetKeyPress(VK_LEFT))
    {
        pos.x -= 0.5f;
    }
    SetPosition(pos.x, pos.y, pos.z);
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

//=======================================
//�`�揈��
//=======================================
void TitleCamera::Draw()
{

}

//=======================================
//�I������
//=======================================
void TitleCamera::Uninit()
{


}

