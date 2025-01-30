#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../08_Collider/BoxCollider.h"
#include "../../03_GameMainFile/Math.h"

const float groundY = 0.0f; // �n�ʂ�Y���W
const float groundX = 0.0f; // �n�ʂ�Y���W

class GameBlock :public Object
{
public:
	GameBlock();
	GameBlock(float posX, float posY, float sizeX, float sizeY);
	~GameBlock() { Uninit(); }
	void Init();  //������
	void Update();//�X�V

	float GetFrictionRasistance();
	float GetOldAngle();
protected:
	void CorrectPointerPosition(float angle);
	void CorrectStonePosition(float angle);
	void CorrectSnowmanPosition(float angle);

private:
	ContactPointVector collision;
	float oldAngle = GetAngle();
	float frictionRasistance;	//���C�W��
};

