#pragma once
#include "../../06_Scene/Scene.h"
#include"SelectBackGround.h"

class SelectScene : public Scene
{
private:
	Object sample;
	SelectBackGround backGround;
	std::vector<Object*> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g

public:
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��

};

extern SelectScene* titleScene;
