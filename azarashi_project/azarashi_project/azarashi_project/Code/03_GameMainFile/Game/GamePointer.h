#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../02_Input/miyoshi_input/ControllerInput.h"
#include "../../03_GameMainFile/RigidBody.h"
#include"../../08_Collider/Base_collision.h"
#include "GameBlock.h"
#include "../../09_Sound/sound.h"

#define AZARASHI_PICTURE_CIRCLE L"Asset/pic/Player_Round_Copy.png"
#define AZARASHI_PICTURE_STAND  L"Asset/pic/Player_Idle_Copy.png"

#define FORCE_JUMP 23.0f

#define SIZE_POINTER_CIRCLE 128.0f
#define SIZE_POINTER_STAND  194.7f

class GamePointer :public Object
{
public:

	GamePointer() {};
	GamePointer(float posX, float posY, float sizeX, float sizeY) : Object(posX, posY, sizeX, sizeY) {};
	~GamePointer() { Uninit(); };
	void Init();  //������
	void Update();//�X�V


	float GetCircleRadius();		//���a�̃Q�b�^�[
	float GetFrictionResistance();	//���C��R�̃Q�b�^�[

	void  RotateTexture();					//�摜�𒚓x�悭��]
	AZA_MODE_NUMMBER azaNum = STAND;
	AZA_MODE_NUMMBER oldAzaNum = azaNum;

	void PointerJump(float angle);

	ID3D11ShaderResourceView* LoadTexture(const wchar_t* filename);


	bool isChangeMode();									//�A�U���V�̃��[�h��r
	void SetAzaNum(AZA_MODE_NUMMBER m_azaNum);				//�A�U���V�̉摜�Z�b�g

	void CorrectPosition(Object& block, float distance, float angle);		//���W�̕␳

	int GetNowHits();
	void NowHitsCounter(int count);

	Object* GetHitGameBlock(int objCount);

	float damping = 0.9f;									//�����W��

private:
	Circle circle;				//
	RigidBody body;										//������������������
	const float AZARASHI_MODE[MODENUM] = { 0.1 , 0.9 };	// ���C�W��
	//�e�N�X�`���p�ϐ�
	ID3D11ShaderResourceView* textures[2];

	BODY_BEHAVIOR behavior = BOUND;		//�A�U���V�̋����̏��
	int boundCounter = 0;				//���񐔃o�E���h������]�����ԂɂȂ�
	const int boundLimmit = 4;
	float oldVectorNum = 0;				//vector�̍����o�����߂̕ۑ��p

	int now ;
	ContactPointVector collision;
	ContactPointVector myCollision;
	float blockAngle;

	Object* m_Block = nullptr;
	Object* m_Blocks[2] = { nullptr,nullptr };
};
