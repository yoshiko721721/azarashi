#include "Stage2UI.h"
void Stage2UI::Init()
{
	/*for (int i = 0; i < 4; i++)
	{
		textures[i] = LoadTexture(imgname[i]);
	}*/

	//SetTexture(textures[0]);
	Initialize(imgname[0]);   //�w�i��������
	SetPos(-240.0f, -170.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(550.0f, 550.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void Stage2UI::Update(int selectPage)//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{
	SetTexture(imgname[selectPage]);
}
