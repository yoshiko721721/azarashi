#include "GamePointer.h"
#include "../../03_GameMainFile/Math.h"

using DirectX::XMFLOAT3 ;

//=========================================
//				����������
//=========================================
void GamePointer::Init()
{
	Initialize(L"Asset/pic/point.png");   //�w�i��������
	SetPos(   0.0f,   0.0f, 0.0f);		  //�ʒu��ݒ�
	SetSize(100.0f, 100.0f, 0.0f);		  //�傫����ݒ�
	SetAngle(0.0f);						  //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);	  //�F��ݒ�

	circle.radius = GetPos().y / 2;

	body.SetMass(7.0f);					  //���ʂ�ݒ�
	body.SetTime(0.01);					  //���Ԃ�������
	body.SetMag(7.0f);					  //�{����ݒ�
	body.SetVector(0.0f, 0.0f);

}

//===========================================
//				�X�V����					
//===========================================

void GamePointer::Update(float blockAngle)//Player�̃A�b�v�f�[�g
{
	Vector2 pos = { GetPos().x,GetPos().y };

	body.TimeCounter(FRAMERATE);
	body.Update(pos, body.GetTime());		//���Ԃ������ɂ��ĕ����̍X�V����

	body.HorizonUpdate(&body.vector,				//�������̍X�V
						GetFrictionResistance(),
						GetAngle());


	pos.x += body.GetVector().x;			//
	pos.y += body.GetVector().y;			//�Ō�Ɉʒu���ړ��������X�V

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

//���ɓ]��������������]����
void GamePointer::RotateTexture(const float sub)  //�����@�F�@�����������̖̂��C��R
{
	float tempAngle = GetAngle();

	if (body.GetVector().x < 0)
		tempAngle -= body.GetVector().x + frictionResistance * sub;
	else if (body.GetVector().x > 0)
		tempAngle -= body.GetVector().x + frictionResistance * sub;

	SetAngle(tempAngle);
}

//���W�̕␳
void GamePointer::CorrectionPos(Object* p_player, Object* p_block)
{

}
