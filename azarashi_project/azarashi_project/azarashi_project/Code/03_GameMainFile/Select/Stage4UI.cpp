#include "Stage4UI.h"

//ID3D11ShaderResourceView* LoadTexture(const wchar_t*);

void Stage4UI::Init()
{
	/*for (int i = 0; i < 4; i++)
	{
		textures[i] = LoadTexture(imgname[i]);
	}*/

	//SetTexture(textures[0]);
	Initialize(imgname[0]);   //”wŒi‚ð‰Šú‰»
	SetPos(620.0f, -170.0f, 0.0f);      //ˆÊ’u‚ðÝ’è
	SetSize(550.0f, 550.0f, 0.0f);  //‘å‚«‚³‚ðÝ’è
	SetAngle(0.0f);                //Šp“x‚ðÝ’è
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//Šp“x‚ðÝ’è
}

void Stage4UI::Update(int selectPage)//”wŒi‚ÌƒAƒbƒvƒf[ƒg(‚¢‚ç‚È‚¢‹C‚ª‚·‚é)
{
	SetTexture(imgname[selectPage]);
}
