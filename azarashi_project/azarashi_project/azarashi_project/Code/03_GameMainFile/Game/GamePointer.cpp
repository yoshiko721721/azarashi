#include "GamePointer.h"
#include "../../03_GameMainFile/Math.h"

using DirectX::XMFLOAT3;

//=========================================
//				����������
//=========================================
void GamePointer::Init()
{
	Initialize(AZARASHI_PICTURE_STAND);   //�w�i��������
	SetPos(0.0f, 0.0f, 0.0f);		  //�ʒu��ݒ�
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

void GamePointer::Update(ContactPointVector collision, Object& block)//Player�̃A�b�v�f�[�g
{

	Vector2 blockPos = { block.GetPos().x, block.GetPos().y };
	now = collision.checkCollision;

	//���R����
	body.FreeFall(body.GetTime());

	//�Փ˂��Ă���̏���
	if (now)
	{

		body.CalcFainalNormalAngle(collision.closspoint, *this, block);	//�@���̊p�x���v�Z
		body.HorizonUpdate(block, AZARASHI_MODE[azaNum]);			//�]���鏈��

		//�W�����v
		if (Input::GetKeyTrigger(VK_RETURN)) {
			body.AddForce(0.0f, 15.0f);
		}



		body.DampingVector(damping, azaNum);
		body.Repulsion();			//����

		//���W��␳
		GamePointer::CorrectPosition(&block, collision.closspoint,
			collision.DistanceSquared, block.GetAngle());

	}


	//���[�h�؂�ւ�
	if (Input::GetKeyPress(VK_T)) {
		SetAzaNum(CIRCLE);
	}
	else {
		SetAzaNum(STAND);
	}

	//���[�h�`�F���W
	if (isChangeMode()) {
		switch (azaNum) {
		case CIRCLE: Initialize(AZARASHI_PICTURE_CIRCLE); break;
		case STAND:  Initialize(AZARASHI_PICTURE_STAND);
			SetAngle(block.GetAngle());			  break;
		}
	}

	//�����蔻��̋L�^
	old = now;
	SetPos(GetPos().x + body.GetVector().x, GetPos().y + body.GetVector().y, 0);

}

float GamePointer::GetCircleRadius()
{
	return circle.radius;
}

float GamePointer::GetFrictionResistance()
{
	return AZARASHI_MODE[azaNum];
}

//���ɓ]��������������]����
void GamePointer::RotateTexture(const float sub)  //�����@�F�@�����������̖̂��C��R
{
	float tempAngle = GetAngle();

	if (body.GetVector().x < 0)
		tempAngle -= body.GetVector().x + AZARASHI_MODE[azaNum];
	else if (body.GetVector().x > 0)
		tempAngle -= body.GetVector().x + AZARASHI_MODE[azaNum];

	tempAngle -= body.vector.x;

	SetAngle(tempAngle);
}

bool GamePointer::isChangeMode()
{
	if (azaNum != oldAzaNum) {
		return true;
	}
	return false;
}

void GamePointer::SetAzaNum(AZA_MODE_NUMMBER m_AzaNum)
{
	oldAzaNum = azaNum;
	azaNum = m_AzaNum;
}

/// @brief ���W�̕␳
/// @param m_Block	���������u���b�N�̈���
/// @param clossPoint �~�Ǝl�p�`�̐ڒn�_
/// @param distanceSquared �~�̒��S���W��clossPoint�̋�����2��
/// @param angle block�̊p�x
void GamePointer::CorrectPosition(Object* m_Block, XMFLOAT2 clossPoint, float distanceSquared, float angle)
{
	float distance = sqrt(distanceSquared);				//�����ȋ����ɂ���
	float overlap = (GetSize().y / 2) - distance;		//�~�̔��a
	XMFLOAT2 direction = { GetPos().x - clossPoint.x, GetPos().y - clossPoint.y };
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction = { direction.x / length, direction.y / length };


	SetPos(GetPos().x + direction.x * overlap, GetPos().y + direction.y * overlap, 0);
}

