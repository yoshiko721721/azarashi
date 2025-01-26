#pragma once
#include "../../06_Scene/Scene.h"
#include "TitleBackGround.h"
#include "TitleBackGroundPAB.h"
#include "../../09_Sound/sound.h"
#include "TitleLogo.h"
#include "../../13_Effect/FadeEffect.h"
#include "TeamLogo.h"
//#include "You_Fade/Fade.h"
//#include "../You_Load/Load.h"

class TitleScene : public Scene
{
private:
	//Object sample;
	TitleBackGround backGround;  //タイトル背景
	TitleBackGroundPAB backGroundpab;//タイトルのボタン指示
	TitleLogo titleLogo;//タイトルロゴ
	FadeEffect fade;
	TeamLogo teamLogo;
	bool isFading = true;//フェードが終わっているか
	//Fade fade;
	//Load load;
	bool isFirst; //初めてタイトルを起動するかどうか
public:
	TitleScene(bool isFrstTitle)
	{
		isFirst = isFrstTitle;
	};
	~TitleScene() {  }
	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画
	void Uninit();		//終了
};

extern TitleScene* titleScene ;