 #include "Stage1UI.h"
void Stage1UI::Init()
{
	/*for (int i = 0; i < 4; i++)
	{
		textures[i] = LoadTexture(imgname[i]);
	}*/
	//SetTexture(textures[0]);
	Initialize(imgname[0]);   //”wŒi‚ð‰Šú‰»
	SetPos(-580.0f,50.0f, 0.0f);      //ˆÊ’u‚ðÝ’è
	SetSize(500.0f, 500.0f, 0.0f);  //‘å‚«‚³‚ðÝ’è
	SetAngle(0.0f);                //Šp“x‚ðÝ’è
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//Šp“x‚ðÝ’è
}

void Stage1UI::Update(int selectPage)//”wŒi‚ÌƒAƒbƒvƒf[ƒg(‚¢‚ç‚È‚¢‹C‚ª‚·‚é)
{
	SetTexture(imgname[selectPage]);
}
