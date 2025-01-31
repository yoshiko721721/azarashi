#include "Stone.h"
#include "../../../03_GameMainFile/Math.h"
#include "../../../08_Collider/BoxCollider.h"
#include"../../Application.h"
#include<vector>

using DirectX::XMFLOAT3;
const float LIMMIT = 0.1;
const float ROLLINGSPEED = 5.0f;


//=========================================
//				����������
//=========================================
void Stone::Init()
{
	Initialize(L"Asset/pic/Rock1.png");   
	SetSize(100.0f, 100.0f, 0.0f);		  //�傫����ݒ�
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

void Stone::Update()//Player�̃A�b�v�f�[�g
{
	std::vector<GameBlock*> blocks = Application::GetInstance()->GetObjects<GameBlock>();
	int hitObj = 0;
	for (auto& block : blocks) {
		collision = BoxCollider::ColliderWithCircle(this, block);
		if (collision.checkCollision != NO_COLLISION) {
			m_Block = block;
			if (hitObj < 2) {
				m_Blocks[hitObj] = block;
				hitObj++;
			}
			NowHitsCounter(1);
		}
	}
	switch (hitObj) {
	case 0: m_Blocks[0] = nullptr;
	case 1: m_Blocks[1] = nullptr;
	}

	//���R����
	if (now < 1 && behavior == BOUND) {
		body.FreeFall(body.GetTime());
	}


	//�Փ˂��Ă���̏���
	if (now == 1)
	{
		body.CalcFinalNormalAngle(collision, *this, *m_Block);	//�@���̊p�x���v�Z

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
			body.HorizonUpdate(*this, *m_Block, Stone_Friction, ROLLINGSPEED);			//�]���鏈��
			break;
		}

		//�W�����v
		if (Input::GetKeyTrigger(VK_RETURN)) {
			body.AddForce(0.0f, 35.0f);
			behavior = BOUND;
		}

		//���W��␳
		CorrectPosition(*m_Block, collision, m_Block->GetAngle());

	}
	else {
		behavior = BOUND;
	}


	//���O�̓����蔻����L��
	oldVectorNum = body.vectorNum;
	SetPos(GetPos().x + body.GetVector().x, GetPos().y + body.GetVector().y, 0);
}

float Stone::GetCircleRadius()
{
	return circle.radius;
}

float Stone::GetFrictionResistance()
{
	return Stone_Friction;
}

//���ɓ]��������������]����
void Stone::RotateTexture()  //�����@�F�@�����������̖̂��C��R
{
	float tempAngle = GetAngle();

	if (body.GetVector().x < 0)
		tempAngle -= body.GetVector().x + Stone_Friction;
	else if (body.GetVector().x > 0)
		tempAngle -= body.GetVector().x + Stone_Friction;

	tempAngle -= body.vector.x;

	SetAngle(tempAngle);
}

/// @brief ���W�̕␳
/// @param m_Block	���������u���b�N�̈���
/// @param clossPoint �~�Ǝl�p�`�̐ڒn�_
/// @param distanceSquared �~�̒��S���W��clossPoint�̋��� 
/// @param angle block�̊p�x
void Stone::CorrectPosition(Object& block, ContactPointVector collision, float angle)
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
	cout << "�@���x�N�g�� = " << Math::ConvertToDegree(body.GetFinalAngle()) << "\n";

	SetPos(GetPos().x + blockNormal.x * overlap, GetPos().y + blockNormal.y * overlap, 0);

}

int Stone::GetNowHits()
{
	return now;
}

void Stone::NowHitsCounter(int count)
{
	now += count;
}

Object* Stone::GetHitGameBlock(int objCount)
{
	if (objCount < 2) {
		return m_Blocks[objCount];
	}
	return nullptr;
}
