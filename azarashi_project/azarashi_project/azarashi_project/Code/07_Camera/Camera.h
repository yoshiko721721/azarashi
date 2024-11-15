#pragma once
#include"../02_Input/input.h"
class Camera
{
public:
    Camera();
    ~Camera();
    void Init();
    void Update();
    void Draw();
    void Uninit();

    //�Z�b�^�[
    void SetPosition  (float x, float y, float z);               //camera�̈ʒu���Z�b�g����
    void SetRotation  (DirectX::XMFLOAT3& rotation);             //camera�̉�]���Z�b�g����
    void GetViewMatrix(DirectX::XMMATRIX viewMatrix);            //���l������Ă���
    void GetProjectionMatrix(DirectX::XMMATRIX projectionMatrix);//���l������Ă���

    //�Q�b�^�[
    DirectX::XMFLOAT3 GetPosition();
    DirectX::XMFLOAT3 GetRotation();
    DirectX::XMMATRIX GetViewMatrix();      //���l������Ă���
    DirectX::XMMATRIX GetProjectionMatrix();//���l������Ă���

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

protected:
    DirectX::XMFLOAT3 m_position = { 0.0f,0.0f,0.0f };//camera�̈ʒu�p�̕ϐ�
    DirectX::XMFLOAT3 m_rotation;//camera�̉�]���p�̕ϐ�
    DirectX::XMMATRIX m_viewMatrix;//�������]���Ȃǂ��v�Z���A�`����e�����߂�����
    DirectX::XMMATRIX m_projectionMatrix;
};

