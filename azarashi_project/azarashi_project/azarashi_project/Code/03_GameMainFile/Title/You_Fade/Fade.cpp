#include "Fade.h"

void Fade::Init ( ) {
	Initialize ( L"Asset/pic/Logo_Team.png" );   //背景を初期化
	SetPos ( 0.0f , 0.0f , 0.0f );      //位置を設定
	SetColor ( 0.0f , 0.0f , 0.0f , 1.0f );
	SetSize ( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f ); //大きさを設定
	fademode = FadeIn;
	fadeInCounter = 0.0f;
	fadeOutCounter = 0.25f;
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 1.0f;
}

void Fade::Update ( void )
{

	switch ( fademode )
	{
	case FadeIn:
		fadeInCounter += 0.4f / 60.0f;
		r = fadeInCounter;
		g = fadeInCounter;
		b = fadeInCounter;
		SetColor ( r , g , b , a );
		if ( fadeInCounter>5.0f )
		{
			fademode = FadeOut;
		}
		break;
	case FadeOut:
		fadeOutCounter-= 0.4f / 60.0f;
		a = fadeOutCounter;
		SetColor ( r , g , b , a );
		break;
	}
}