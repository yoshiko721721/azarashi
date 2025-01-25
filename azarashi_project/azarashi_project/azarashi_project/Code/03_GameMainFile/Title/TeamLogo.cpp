#include "TeamLogo.h"
void TeamLogo::Init()
{
	/*for (int i = 0; i < 4; i++)
	{
		textures[i] = LoadTexture(imgname[i]);
	}*/

	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/TeamLogo.png");   //”wŒi‚ð‰Šú‰»
	SetPos(0.0f, 0.0f, 0.0f);      //ˆÊ’u‚ðÝ’è
	SetSize(1920.0f, 1080.0f, 0.0f);  //‘å‚«‚³‚ðÝ’è
	SetAngle(0.0f);                //Šp“x‚ðÝ’è
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//Šp“x‚ðÝ’è
}

void TeamLogo::Update()//”wŒi‚ÌƒAƒbƒvƒf[ƒg(‚¢‚ç‚È‚¢‹C‚ª‚·‚é)
{

}
