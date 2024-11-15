#pragma once
#include "camera.h"
#include "input.h"
using DirectX::XMFLOAT2;

class GameCamera :public Camera
{
public:
	void Init();
	void Update(float targetPosX,float targetPosY);
	void Draw();
	void Uninit();

	GameCamera();
	GameCamera(float, float);

	void SetPosition(float x, float y);				//���W�Z�b�^�[
	DirectX::XMMATRIX GetViewMatrix() const;		//�r���[�s��Q�b�^�[
	DirectX::XMMATRIX GetProjectionMatrix() const;	//�ˉe�s��Q�b�^�[


private:
	Input input;
	DirectX::XMFLOAT3 position;				//�J�������W
	DirectX::XMMATRIX viewMatrix;			//�r���[�s��
	DirectX::XMMATRIX projectionMatrix;		//�ˉe�s��
	DirectX::XMFLOAT2 target;				//�J�����̊�ɂȂ�A�U���V�̍��W���i�[����ϐ�

	void updateViewMatrix();				//�r���[�s��X�V
};