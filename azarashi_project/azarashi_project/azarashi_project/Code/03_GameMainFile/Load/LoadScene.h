#pragma once
#include "../../06_Scene/Scene.h"
#include "LoadBackGround.h"
#include "LoadBackGroundPAB.h"

class LoadScene : public Scene
{
private:
	LoadBackGround backGround;
	LoadBackGroundPAB backGroundpab;
public:
	LoadScene() {};
	~LoadScene() {  }
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��
};

extern LoadScene* loadScene;
