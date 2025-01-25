#include "FadeEffect.h"

//フェード・イン/アウト時間をリーダーの要望により調整してお願いします

void FadeEffect::Init ( ) {
	Initialize ( L"Asset/pic/Logo_Team.png" );   //背景を初期化
	SetPos ( 0.0f , 0.0f , 0.0f );      //位置を設定
	SetColor ( 1.0f , 1.0f , 1.0f , 1.0f );		//色を設定
	SetSize ( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f ); //大きさを設定
	fademode = FADEIN;			//フェードモードを初期化
	fadeInCounter = 0.0f;			//フェイド・インカウントを初期化
	fadeOutCounter = 0.0f;//フェイド・アウトカウントを初期
	a = 1.0f;			//透明度変数を初期化
	isFading = true;
}

bool FadeEffect::Update ( float fadeTime )
{
	if (isFading)
	{
		switch (fademode)
		{
		case FADEIN:		//フェイドを表示
			fadeInCounter += fadeTime / 60.0f;		//徐々に透明度を上げる
			/*r = fadeInCounter;
			g = fadeInCounter;
			b = fadeInCounter;*/
			a -= fadeInCounter;
			SetColor(1.0, 1.0, 1.0, a);						//色を設定
			if (a < 0.0f)					//フェード・インが一定時間経た
			{
				//fademode = FadeOut;	//モードチェンジ
				isFading = false;
				fadeInCounter = 0;
				return isFading;
			}
			return isFading;
			break;
		case FADEOUT:		//フェイドを終了
			fadeOutCounter += fadeTime / 60.0f;		//一秒毎0.4マイナス
			//フェード画面がだんだん薄くなて、表示しないように
			a += fadeOutCounter;
			SetColor(1.0f, 1.0f, 1.0f, a);
			if (a > 1.0f)					//フェード・インが一定時間経た
			{
				isFading = false;
				fadeOutCounter = 0;
				return isFading;
			}
			//色を設定
			return isFading;
			break;

		}
	}

}