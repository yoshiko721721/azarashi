#pragma once
#include <DirectXMath.h>
#include "direct3d.h"

//-----------------------------------------------------------------------------
//Camera�N���X
//-----------------------------------------------------------------------------
class Camera 
{
public:
    Camera();
	~Camera();
    void Init();
    void Update();
    void Draw();
    void Uninit();

    void SetPosition(float x, float y, float z);//camera�̈ʒu���Z�b�g����
    void SetRotation(DirectX::XMFLOAT3& rotation);//camera�̉�]���Z�b�g����
    DirectX::XMMATRIX GetViewMatrix();      //���l������Ă���
    DirectX::XMMATRIX GetProjectionMatrix();//���l������Ă���
    DirectX::XMFLOAT3 GetPosition();
    DirectX::XMFLOAT3 GetRotation();

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

protected:
    DirectX::XMFLOAT3 m_position = { 0.0f,0.0f,0.0f };//camera�̈ʒu�p�̕ϐ�
    DirectX::XMFLOAT3 m_rotation;//camera�̉�]���p�̕ϐ�
    DirectX::XMMATRIX m_viewMatrix;//�������]���Ȃǂ��v�Z���A�`����e�����߂�����
    DirectX::XMMATRIX m_projectionMatrix;

};
