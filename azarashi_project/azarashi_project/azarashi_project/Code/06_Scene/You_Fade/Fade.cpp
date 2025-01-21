#include "Fade.h"

//フェード・イン/アウト時間をリーダーの要望により調整してお願いします

void Fade::Init ( ) {
	Initialize ( L"Asset/pic/Fade.png" );   //フェードを初期化 (真っ黒の図形でいい)
	SetPos ( 0.0f , 0.0f , 0.0f );      //位置を設定
	SetColor ( 1.0f , 1.0f , 1.0f , 1.0f );		//色を設定
	SetSize ( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f ); //大きさを設定
	fademode = FadeOut;			//フェードモードを初期化
	fadeOutCounter = 1.0f;		//フェイド・アウトカウントを初期化
	//フェイド・アウトカウント値はフェイド・アウト実行する秒数
	fadeInCounter = 0.0f;			//フェイド・インカウントを初期化

	a = 1.0f;			//透明度変数を初期化
}

void Fade::Update ( void )
{
	fadeOutCounter = 1.0f;		//Update毎にリセット
	fadeInCounter = 0.0f;			//Update毎にリセット
	switch ( fademode )
	{
	case FadeOut:		//フェイドを終了
		fadeOutCounter -= 0.0167f;		//fadeOutCounter 1フレーム毎にマイナス値
		fadeInCounter += 0.0167f;		//fadeInCounter 1フレーム毎にマイナス値
		//フェード画面がだんだん薄くなて、表示しないように
		a = fadeOutCounter;
		SetColor ( 1.0f , 1.0f , 1.0f , a );						//色を設定
		if ( fadeInCounter > 3.0f )					//フェード・アウトが一定時間経た
			//3.0はフェード・アウト後表示する画面の秒数プラス1秒の結果（現在フェード・アウトは1秒）
		{
			fadeInCounter = 0.0f;						//fadeInCounterをリセット
			fademode = FadeIn;					//モードチェンジ
		}
		break;
	case FadeIn:		//フェイドを表示
		fadeInCounter += 0.0167f;		//1フレーム毎にプラス値	（今の設定は実行時間は1秒）
		//フェード・アウト終了、フェイド・インを実行する（画面が真っ黒になる）
		a = fadeInCounter;
		SetColor ( 1.0f , 1.0f , 1.0f , a );						//色を設定

		break;
	}
}