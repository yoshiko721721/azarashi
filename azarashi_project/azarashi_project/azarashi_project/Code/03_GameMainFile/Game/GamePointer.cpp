#include "GamePointer.h"
using DirectX::XMFLOAT3 ;
void GamePointer::Init()
{
	Initialize(L"Asset/pic/point.png");   //背景を初期化
	SetPos(0.0f, 500.0f, 0.0f);      //位置を設定
	SetSize(100.0f, 100.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//角度を設定

}

void GamePointer::Update(void)//Playerのアップデート
{
	input.Update();
	DirectX::XMFLOAT3 pos = GetPos();

	// 1. 重力の適用
	circle.velocityY += gravity;
	pos.y += circle.velocityY;
	pos.x += circle.velocityX;

	//circle.velocityY += gravity;
	pos.y += circle.velocityY;
	if (pos.x >= groundX - 300 && pos.x <= groundX + 300 && pos.y <= groundY + 25 + circle.radius /* && pos.y >= groundY + 50 + circle.radius&&*/)
	{
		pos.y = groundY + circle.radius + 23; // 地面の上に位置を修正
		///circle.velocityY = 0.0f;			// 速度をゼロにして停止
	}
		/*// 地面法線ベクル
		float nx = sin(30.0f);
		float ny = cos(30.0f);

		// 法線方向の速度成分
		float normalVelocity = circle.velocityX * nx + circle.velocityY * ny;

		  // 反発係数（摩擦がある場合、少し減少させる）
		float restitution = 0.8f;  // 例: 反発係数80%

		// 衝突後の速度計算
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

