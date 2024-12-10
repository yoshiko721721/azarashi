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
void GameCamera::Update(float targetPosX,float targetPosY)
{

    target = { targetPosX ,targetPosY };        //��̃^�[�Q�b�g���W����
    DirectX::XMFLOAT3 pos = GetPosition();

    //// �P�ʃx�N�g���擾
    //DirectX::XMFLOAT3 player_to_target = DirectX::XMFLOAT3(target.x - player_pos.x, target_pos.y - player_pos.y, target_pos.z - player_pos.z);
    //float length = sqrtf(powf(player_to_target.x, 2.0f) + powf(player_to_target.y, 2.0f) + powf(player_to_target.z, 2.0f));
    //DirectX::XMFLOAT3 unitvec_player_to_target = DirectX::XMFLOAT3(player_to_target.x / length, player_to_target.y / length, player_to_target.z / length);



    if (Input::GetKeyPress(VK_RIGHT))
    {
        pos.x += 5.0f;
    }
    SetPosition(pos.x, pos.y);
    GetViewMatrix();
    GetViewMatrix();
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

//�R���X�g���N�^���|�g�p���Ȃ�
GameCamera::GameCamera()
{
}

//�R���X�g���N�^
GameCamera::GameCamera(float screenWidth, float screenHeight)
{
    
}


//���W�Z�b�^�[
void GameCamera::SetPosition(float x, float y)
{
    
}

//�r���[�s��Q�b�^�[
DirectX::XMMATRIX GameCamera::GetViewMatrix() const
{
    return viewMatrix;
}

//�ˉe�s��Q�b�^�[
DirectX::XMMATRIX GameCamera::GetProjectionMatrix() const
{
    return projectionMatrix;
}

//�ˉe�s��X�V
void GameCamera::updateViewMatrix()
{
    viewMatrix = DirectX::XMMatrixTranslation(-position.x, -position.y, 0.0f); 
}





