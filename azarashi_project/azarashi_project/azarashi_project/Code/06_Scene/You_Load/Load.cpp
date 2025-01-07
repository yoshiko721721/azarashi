#include "Load.h"
void Load::Init ( ) {
	std::random_device rd;		//ランダム変数
	std::mt19937 gen ( rd ( ) );		//ランダム変数
	std::uniform_int_distribution<int> distLoad ( 0 , 2 );	//ランダム範囲0～2
	int randLoad = distLoad ( gen );		//ランダム変数
	//ランダム読み込めるように
	switch ( randLoad ) {
	case 0:
		Initialize ( L"asset/loading.png" );//テクスチャタイプ0を初期化
		break;
	case 1:
		Initialize ( L"asset/loading1.png" );//テクスチャタイプ１を初期化
		break;
	case 2:
		Initialize ( L"asset/loading2.png" );//テクスチャタイプ２を初期化
		break;
	}
	SetPos ( 0.0f , 0.0f , 0.0f );      //位置を設定
	SetColor ( 1.0f , 1.0f , 1.0f , 1.0f );		//色を設定
	SetSize ( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f ); //大きさを設定

}
void Load::Update ( ) {
	input.Update ( );		//インプット更新
	isLoading = true;		//ローディング開始
	if ( isLoading )
	{
		loadCounter++;		//ロードカウンター
		if ( loadCounter >= 60 )	//１秒間は60フレーム
		{
			//AnyKeyを設定したい場合はInputにAnyKeyTrigger関数を用意してお願いします
			if ( GetAsyncKeyState ( VK_SPACE ) )	//一応スペースキーを設定
			{
				isLoading = false;	//ローディング終了
				nextscene = 1;		//シーンの番号に値を代入して
			}
		}
		scene = nextscene;		//シーンを切り替え
	}
		return;
}