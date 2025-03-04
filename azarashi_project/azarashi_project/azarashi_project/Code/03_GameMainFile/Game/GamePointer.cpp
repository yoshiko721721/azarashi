#include "GamePointer.h"
#include "../../03_GameMainFile/Math.h"
#include "../../08_Collider/BoxCollider.h"
#include "../../07_Camera/Camera.h"
#include"../Application.h"
#include<vector>

using DirectX::XMFLOAT3;
const float LIMMIT = 0.1;
const float ROLLINGSPEED = 5.0f;

extern Sound sound;

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
	SetSize(SIZE_POINTER_STAND, SIZE_POINTER_CIRCLE, 0.0f);
	circle.radius = GetPos().y / 2;

	body.SetMass(7.0f);					  //���ʂ�ݒ�
	body.SetTime(0.01);					  //���Ԃ�������
	body.SetMag(7.0f);					  //�{����ݒ�
	body.SetVector(0.0f, 0.0f);

	textures[CIRCLE] = LoadTexture(AZARASHI_PICTURE_CIRCLE);
	textures[STAND]  = LoadTexture(AZARASHI_PICTURE_STAND);
	
		now = 0;
}

//===========================================
//				�X�V����					
//===========================================

void GamePointer::Update()//Player�̃A�b�v�f�[�g
{
	//Camera::UnLock();
	Controller::Input::Update();
	std::vector<GameBlock*> blocks = Application::GetInstance()->GetObjects<GameBlock>();
	int hitObj = 0;
	float nrmAngle = 0.0f;
	float distance = 0.0f;
	for (auto& block : blocks) {
		collision = BoxCollider::ColliderWithCircle(this, block);
		if (collision.checkCollision != NO_COLLISION) {
			m_Block = block;
			myCollision = collision;
			distance += collision.distanceSquared;
			nrmAngle += body.CalcFinalNormalAngle(myCollision, *this, *block);	//�@���̊p�x���v�Z
			if (hitObj < 4) {
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
	else if (hitObj > 0) {
		//���W��␳
		nrmAngle /= (float)hitObj;
		distance /= (float)hitObj;
		CorrectPosition(*m_Block, distance, nrmAngle);

	}


	//�Փ˂��Ă���̏���
	if (now == 1)
	{
		
		if (m_Block != nullptr)
		{

			

			if (behavior == ROLLING || boundCounter >= 4) {
				body.HorizonUpdate(*this, *m_Block, AZARASHI_MODE[azaNum], ROLLINGSPEED);			//�]���鏈��
			}
			else {
				boundCounter++;
				body.Repulsion();			//����
			}
			

			//�W�����v
			if (Input::GetKeyTrigger(VK_RETURN) || Input::GetButtonTrigger(XINPUT_A)) 
			{
				sound.Play(SOUND_LABEL_SE4);
				PointerJump(myCollision.closspoint.normalAngle);
				behavior = BOUND;
				boundCounter = 0;
			}


		}
	}
	else {
		behavior = BOUND;
	}


	//���[�h�؂�ւ�
	if ((Controller::Input::GetLeftTrigger()   > 0 && Controller::Input::GetLeftTrigger() <= 1) &&
		(Controller::Input::GetRightTrigger() >= 0 && Controller::Input::GetRightTrigger() <= 1) || 
		Input::GetKeyPress(VK_T))
	{
		SetAzaNum(CIRCLE);
	}
	else 
	{
		SetAzaNum(STAND);
	}
	//���[�h�`�F���W
	if (isChangeMode()) {
		switch (azaNum) {
		case CIRCLE: m_pTextureView = textures[CIRCLE]; 
					 SetSize(SIZE_POINTER_CIRCLE, SIZE_POINTER_CIRCLE, 0.0f);
			break;
		case STAND:  m_pTextureView = textures[STAND];  
					 float standAngle = myCollision.closspoint.normalAngle - 90.0f;
					 SetSize(SIZE_POINTER_STAND, SIZE_POINTER_CIRCLE, 0.0f);
					 SetAngle(standAngle);
			break;
		}
	}
	//���ړ��ƘA�������摜�̉�]
	if (azaNum == CIRCLE) {
		RotateTexture();
	}


	//���O�̓����蔻����L��
	oldVectorNum = Math::CalcSquareRoot(body.GetVector().x, body.GetVector().y);
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
		tempAngle -= body.GetVector().x / 10.0f + AZARASHI_MODE[azaNum];
	else if (body.GetVector().x > 0)
		tempAngle -= body.GetVector().x / 10.0f + AZARASHI_MODE[azaNum];

	tempAngle -= body.vector.x;

	SetAngle(tempAngle);
}

void GamePointer::PointerJump(float angle)
{
	Radian forceAngle = Math::ConvertToRadian(angle);
	body.vectorNum = FORCE_JUMP;
	Vector2 force = { body.vectorNum * cos(forceAngle),
					  body.vectorNum * sin(forceAngle)};
	
	body.AddForce(force.x, force.y);
}

ID3D11ShaderResourceView* GamePointer::LoadTexture(const wchar_t* filename)
{
	HRESULT hr = DirectX::CreateWICTextureFromFile(g_pDevice, filename, NULL, &m_pTextureView);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
	}
	return m_pTextureView;
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
void GamePointer::CorrectPosition(Object& block, float distancesqured, float angle)
{
	// �����ȋ������v�Z
	float distance = sqrt(distancesqured);
	// �~�̏d�Ȃ苗�����v�Z
	float overlap = (GetSize().y / 2.0f) - distance;
	// �u���b�N�̉�]�p�x�Ɋ�Â��@���̌v�Z
	XMFLOAT2 blockNormal = {
		cos(angle) * overlap,
		sin(angle) * overlap
	};
	SetPos(GetPos().x + blockNormal.x , GetPos().y + blockNormal.y , 0.0f);

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
