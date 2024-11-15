#include "GamePointer.h"
using DirectX::XMFLOAT3 ;
void GamePointer::Init()
{
	Initialize(L"Asset/pic/point.png");   //�w�i��������
	SetPos(0.0f, 500.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(100.0f, 100.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�

}

void GamePointer::Update(void)//Player�̃A�b�v�f�[�g
{
	input.Update();
	DirectX::XMFLOAT3 pos = GetPos();

	// 1. �d�͂̓K�p
	circle.velocityY += gravity;
	pos.y += circle.velocityY;
	pos.x += circle.velocityX;

	//circle.velocityY += gravity;
	pos.y += circle.velocityY;
	if (pos.x >= groundX - 300 && pos.x <= groundX + 300 && pos.y <= groundY + 25 + circle.radius /* && pos.y >= groundY + 50 + circle.radius&&*/)
	{
		pos.y = groundY + circle.radius + 23; // �n�ʂ̏�Ɉʒu���C��
		///circle.velocityY = 0.0f;			// ���x���[���ɂ��Ē�~
	}
		/*// �n�ʖ@���x�N��
		float nx = sin(30.0f);
		float ny = cos(30.0f);

		// �@�������̑��x����
		float normalVelocity = circle.velocityX * nx + circle.velocityY * ny;

		  // �����W���i���C������ꍇ�A��������������j
		float restitution = 0.8f;  // ��: �����W��80%

		// �Փˌ�̑��x�v�Z
		circle.velocityX -= (1 + restitution) * normalVelocity * nx;
		circle.velocityY -= (1 + restitution) * normalVelocity * ny;*/
	/*if (input.GetKeyPress(VK_LEFT))
	{
		pos.x -= 3.0f;
	}
	if (input.GetKeyPress(VK_RIGHT))
	{
		pos.x += 3.0f;
	}*/
	SetPos(pos.x, pos.y, pos.z);
}

float GamePointer::GetCirclePosX()
{
	return circle.velocityX;
}
float GamePointer::GetCirclePosY()
{
	return circle.velocityY;
}

