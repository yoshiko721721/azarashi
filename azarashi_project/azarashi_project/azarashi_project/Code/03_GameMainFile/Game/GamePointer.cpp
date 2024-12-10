#include "GamePointer.h"
using DirectX::XMFLOAT3 ;
void GamePointer::Init()
{
	Initialize(L"Asset/pic/point.png");   //�w�i��������
	SetPos(-250.0f, 100.0f, 0.0f);			  //�ʒu��ݒ�
	SetSize(100.0f, 100.0f, 0.0f);		  //�傫����ݒ�
	SetAngle(0.0f);						  //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);	  //�F��ݒ�

	circle.radius = GetPos().y / 2;
	body.SetMass(7.0f);					  //���ʂ�ݒ�
	body.SetTime(0.0f);					  //���Ԃ�������
	body.SetMag (7.0f);				  //�{����ݒ�
	body.SetVector(0.0f,0.0f);


}

/// @brief �X�V
/// @param  �Ȃ�
void GamePointer::Update(void)//Player�̃A�b�v�f�[�g
{
	
	Vector2 pos = { GetPos().x,GetPos().y};
	
	body.TimeCounter(FRAMERATE);			//���Ԃ�1 / FPS �v�Z
	body.Update(pos,body.GetTime());
	
	pos.x += body.GetVector().x;
	pos.y += body.GetVector().y;

	SetPos(pos.x, pos.y, 0);
}

float GamePointer::GetCircleRadius()
{
	return circle.radius;
}

float GamePointer::GetFrictionResistance()
{
	return frictionResistance;
}

void GamePointer::RotateTexture(const float sub)  //�����@�F�@�����������̖̂��C��R
{
	float tempAngle = GetAngle();

	if (body.GetVector().x < 0)
		tempAngle -= body.GetVector().x + frictionResistance * sub;
	else if (body.GetVector().x > 0)
		tempAngle -= body.GetVector().x + frictionResistance * sub;

	SetAngle( tempAngle);



}




