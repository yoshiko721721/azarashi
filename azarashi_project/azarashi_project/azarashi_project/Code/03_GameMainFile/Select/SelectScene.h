#pragma once
#include "../../06_Scene/Scene.h"
#include "SelectBackGround.h"
#include "World_UI.h"
#include "../../13_Effect/FadeEffect.h"
#include "Stage1UI.h"
#include "Stage2UI.h"
#include "Stage3UI.h"
#include "Stage4UI.h"
#include "SelectCursorL.h"
#include "SelectCursorR.h"
#include "SelectPlayer.h"
#include "../../09_Sound/sound.h"
#include "SelectTitleBackUI.h"

class SelectScene : public Scene
{
private:
	const int MAX_PAGE = 3;
	Object sample;
	//std::vector<Object*> m_MySceneObjects; // ���̃V�[���̃I�u�W�F�N�g
	SelectBackGround backGround;  //�w�i
	WorldUI worldUI;
	Stage1UI stage1UI;
	Stage2UI stage2UI;
	Stage3UI stage3UI;
	Stage4UI stage4UI;
	SelectCursorL cursorL;
	SelectCursorR cursorR;
	SelectPlayer selectPlayer;
	TitleBackUI titleBackUI;

	FadeEffect fade;  //�t�F�[�h�p�̍����摜�Ȃ�
	bool isFading = true;//�t�F�[�h���I����Ă��邩
	int selectPage = 0;
	int selectStage = 0;
public:
	void Init();		//������
	void Update();		//�X�V
	void Draw();		//�`��
	void Uninit();		//�I��

};