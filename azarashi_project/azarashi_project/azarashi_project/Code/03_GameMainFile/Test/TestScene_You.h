#pragma once
#include "../../06_Scene/Scene.h"

class TestScene_You : public Scene
{
private:

public:
	TestScene_You() {};
	~TestScene_You() {  }
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��
};

extern TestScene_You* testScene_You;
