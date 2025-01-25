#include "GamePointer.h"
#include "../../03_GameMainFile/Math.h"
#include "../../08_Collider/BoxCollider.h"
#include"../Application.h"
#include<vector>

using DirectX::XMFLOAT3;
const float LIMMIT = 0.1;
const float ROLLINGSPEED = 5.0f;


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

void GamePointer::Update()//Player�̃A�b�v�f�[�g
{
	std::vector<GameBlock*> blocks = Application::GetInstance()->GetObjects<GameBlock>();
	for (auto& block : blocks) {
		collision = BoxCollider::ColliderWithCircle(this, block);
		if ( collision.checkCollision) {
			now = collision.checkCollision;
			m_Block = block;
			break;
		}
	}

	//���R����
	if (!now && behavior == BOUND) {
		body.FreeFall(body.GetTime());
	}


	//�Փ˂��Ă���̏���
	if (now)
	{
		body.CalcFainalNormalAngle(collision.closspoint, *this, *m_Block);	//�@���̊p�x���v�Z

		switch (behavior) {
		case BOUND:
			body.Repulsion();			//����
			if ((oldVectorNum - body.vectorNum) < LIMMIT && (oldVectorNum - body.vectorNum) > -LIMMIT) {
				behavior = ROLLING;
				body.vector.x = 0;
				body.vector.y = 0;
			}
			break;
		case ROLLING:
			body.HorizonUpdate(AZARASHI_MODE[azaNum], ROLLINGSPEED);			//�]���鏈��
			break;
		}

		//�W�����v
		if (Input::GetKeyTrigger(VK_RETURN)) {
			body.AddForce(0.0f, 10.0f);
			behavior = BOUND;
		}
		//body.DampingVector(damping, azaNum);

		//���W��␳
		CorrectPosition(m_Block, collision.closspoint,collision.DistanceSquared);
	}
	else {
		behavior = BOUND;
		now = false;
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
		case STAND:  Initialize(AZARASHI_PICTURE_STAND);  break;
		}
	}

	//���O�̃x�N�g�����L��
	oldVectorNum = body.vectorNum;
	SetPos(GetPos().x + body.GetVector().x, GetPos().y + body.GetVector().y, 0);

	//std::cout << "now = " << now << std::endl ;

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
/// @param distanceSquared �~�̒��S���W��clossPoint�̋��� 
/// @param angle block�̊p�x
void GamePointer::CorrectPosition(Object* m_Block, XMFLOAT2 clossPoint, float distanceSquared)
{
	// �����ȋ������v�Z
	float distance = sqrt(distanceSquared);

	// �~�̏d�Ȃ苗�����v�Z
	float overlap = (GetSize().y / 2) - distance;

	// �l�p�`�̖@�����v�Z�i�p�x���l���j
	// �u���b�N�̉�]�p�x�Ɋ�Â��@���̌v�Z
	XMFLOAT2 blockNormal = {
		cos(body.fainalNormalAngle),
		sin(body.fainalNormalAngle)
	};

	// �ړ_����~�̒��S�ւ̃x�N�g�����v�Z
	XMFLOAT2 direction = { GetPos().x - clossPoint.x, GetPos().y - clossPoint.y };
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length > 0.0f) {
		direction = { direction.x / length, direction.y / length };
	}

	// �@�������Ƃ̓��ς��v�Z���ĕ␳�����𒲐�
	float dotProduct = direction.x * blockNormal.x + direction.y * blockNormal.y;
	if (dotProduct < 0) {
		blockNormal = { -blockNormal.x, -blockNormal.y };
	}

	// �␳��K�p
	SetPos(GetPos().x + blockNormal.x * overlap, GetPos().y + blockNormal.y * overlap, 0);
}
