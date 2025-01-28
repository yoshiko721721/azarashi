#pragma once
#include "../../06_Scene/Scene.h"
#include "LoadBackGround.h"
#include "../Title/TitleBackGroundPAB.h"

class LoadScene : public Scene
{
private:
	LoadBackGround backGround;
	TitleBackGroundPAB backGroundpab;
public:
	LoadScene() {};
	~LoadScene() {  }
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��
};

extern LoadScene* loadScene;
