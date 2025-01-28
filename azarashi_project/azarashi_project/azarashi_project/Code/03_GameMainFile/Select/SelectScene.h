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
	//std::vector<Object*> m_MySceneObjects; // このシーンのオブジェクト
	SelectBackGround backGround;  //背景
	WorldUI worldUI;
	Stage1UI stage1UI;
	Stage2UI stage2UI;
	Stage3UI stage3UI;
	Stage4UI stage4UI;
	SelectCursorL cursorL;
	SelectCursorR cursorR;
	SelectPlayer selectPlayer;
	TitleBackUI titleBackUI;

	FadeEffect fade;  //フェード用の黒い画像など
	bool isFading = true;//フェードが終わっているか
	int selectPage = 0;
	int selectStage = 0;
public:
	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画
	void Uninit();		//終了

};