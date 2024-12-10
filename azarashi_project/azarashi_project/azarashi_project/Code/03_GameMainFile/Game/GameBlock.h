#pragma once
#include "../../01_Direct3D/Object.h"
#include "../../02_Input/input.h"
#include "../../08_BoxCollider/BoxCollider.h"

	const float groundY = -200.0f; // �n�ʂ�Y���W
	const float groundX = 0.0f; // �n�ʂ�Y���W

class GameBlock :public Object
{
public:
	GameBlock() {}
	~GameBlock() { Uninit(); }
	void Init();  //������
	void Update();//�X�V

	float GetFrictionRasistance();
	BoxCollider collider;

private:

	float frictionRasistance;	//���C�W��
};

