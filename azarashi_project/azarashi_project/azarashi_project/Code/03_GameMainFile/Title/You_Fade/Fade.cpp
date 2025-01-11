#include "Fade.h"

//フェード・イン/アウト時間をリーダーの要望により調整してお願いします

void Fade::Init ( ) {
	Initialize ( L"Asset/pic/Logo_Team.png" );   //背景を初期化
	SetPos ( 0.0f , 0.0f , 0.0f );      //位置を設定
	SetColor ( 0.0f , 0.0f , 0.0f , 1.0f );		//色を設定
	SetSize ( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f ); //大きさを設定
	fademode = FadeIn;			//フェードモードを初期化
	fadeInCounter = 0.0f;			//フェイド・インカウントを初期化
	fadeOutCounter = 0.25f;		//フェイド・アウトカウントを初期化
	r = 0.0f;			//色R変数を初期化
	g = 0.0f;			//色G変数を初期化
	b = 0.0f;			//色B変数を初期化
	a = 1.0f;			//透明度変数を初期化
}

void Fade::Update ( void )
{

	switch ( fademode )		
	{
	case FadeIn:		//フェイドを表示
		fadeInCounter += 0.4f / 60.0f;		//一秒毎0.4プラス
		//RGBが同時にプラスにより、フェード画面は真っ黒から元々の様子に変化
		r = fadeInCounter;
		g = fadeInCounter;
		b = fadeInCounter;
		SetColor ( r , g , b , a );						//色を設定
		if ( fadeInCounter>3.0f )					//フェード・インが一定時間経た
		{
			fademode = FadeOut;					//モードチェンジ
		}
		break;
	case FadeOut:		//フェイドを終了
		fadeOutCounter-= 0.4f / 60.0f;		//一秒毎0.4マイナス
		//フェード画面がだんだん薄くなて、表示しないように
		a = fadeOutCounter;
		SetColor ( r , g , b , a );						//色を設定
		break;
	}
}