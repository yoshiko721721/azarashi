#include "StageExplanation.h"
void StageExplanation::Init()
{
	/*for (int i = 0; i < 4; i++)
	{
		textures[i] = LoadTexture(imgname[i]);
	}*/

	//SetTexture(textures[0])   //�w�i��������
	Initialize(L"Asset/pic/Controller.png");
	SetPos(0.0f, 0.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void StageExplanation::Update()//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{

}
