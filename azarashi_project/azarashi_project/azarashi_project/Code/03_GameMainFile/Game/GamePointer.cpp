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
	//SetPos(0.0f, 0.0f, 0.0f);		  //�ʒu��ݒ�
	//SetSize(100.0f, 100.0f, 0.0f);		  //�傫����ݒ�
	SetAngle(0.0f);						  //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);	  //�F��ݒ�

	circle.radius = GetPos().y / 2;

	body.SetMass(7.0f);					  //���ʂ�ݒ�
	body.SetTime(0.01);					  //���Ԃ�������
	body.SetMag(7.0f);					  //�{����ݒ�
	body.SetVector(0.0f, 0.0f);

	now = 0;
}

//===========================================
//				�X�V����					
//===========================================

void GamePointer::Update()//Player�̃A�b�v�f�[�g
{
	std::vector<GameBlock*> blocks = Application::GetInstance()->GetObjects<GameBlock>();
	int hitObj = 0;
	for (auto& block : blocks) {
		collision = BoxCollider::ColliderWithCircle(this, block);
		if ( collision.checkCollision != NO_COLLISION) {
			m_Block = block;
			myCollision = collision;
			if (hitObj < 2) {
				m_Blocks[hitObj] = block;
				hitObj++;
			}
			NowHitsCounter(1);
		}
	}

	//���R����
	if (hitObj == 0 && behavior == BOUND) {
			body.FreeFall(body.GetTime());
	}


	//�Փ˂��Ă���̏���
	if (now == 1)
	{
		
		if (m_Block != nullptr)
		{
			body.CalcFinalNormalAngle(myCollision, *this, *m_Block);	//�@���̊p�x���v�Z

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
				body.HorizonUpdate(*this, *m_Block, AZARASHI_MODE[azaNum], ROLLINGSPEED);			//�]���鏈��
				break;
			}

			//�W�����v
			if (Input::GetKeyTrigger(VK_RETURN) || Input::GetButtonTrigger(XINPUT_X)) {
				body.AddForce(0.0f, 25.0f);
				behavior = BOUND;
			}

			//���W��␳
			CorrectPosition(*m_Block, myCollision, m_Block->GetAngle());

		}
		else {
			behavior = BOUND;
		}
	}


	//���[�h�؂�ւ�
	if (Input::GetKeyPress(VK_T) ||
		(Input::GetButtonPress(XINPUT_LEFT_SHOULDER))) {
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
	//���ړ��ƘA�������摜�̉�]
	if (azaNum == CIRCLE) {
		RotateTexture();
	}


	//���O�̓����蔻����L��
	oldVectorNum = body.vectorNum;
	SetPos(GetPos().x + body.GetVector().x, GetPos().y + body.GetVector().y, 0);
	now = 0;
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
void GamePointer::RotateTexture()  //�����@�F�@�����������̖̂��C��R
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
void GamePointer::CorrectPosition(Object& block, ContactPointVector collision, float angle)
{
	// �����ȋ������v�Z
	float distance = sqrt(collision.distanceSquared);
	// �~�̏d�Ȃ苗�����v�Z
	float overlap = (GetSize().y / 2) - distance;
	// �u���b�N�̉�]�p�x�Ɋ�Â��@���̌v�Z
	XMFLOAT2 blockNormal = {
		cos(body.GetFinalAngle()),
		sin(body.GetFinalAngle())
	};
	SetPos(GetPos().x + blockNormal.x * overlap, GetPos().y + blockNormal.y * overlap, 0);

}

int GamePointer::GetNowHits()
{
	return now;
}

void GamePointer::NowHitsCounter(int count)
{
	now += count;
}

Object* GamePointer::GetHitGameBlock(int objCount)
{
	if (objCount < 2) {
		return m_Blocks[objCount];
	}
	return nullptr;
}
