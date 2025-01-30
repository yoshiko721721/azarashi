#include "GameBlock.h"
#include "../../08_Collider/BoxCollider.h"
#include "../../03_GameMainFile/Game/GamePointer.h"
#include "../../03_GameMainFile/Application.h"
#include "../../03_GameMainFile/Game/Gimmick/Stone.h"
#include "../../03_GameMainFile/Game/Gimmick/Snowman.h"
#include <vector>

extern float gyroData[3]; // x, y, z��

GameBlock::GameBlock()
{
	collision.checkCollision = NO_COLLISION;
	collision.closspoint = { -1,-1 };
	collision.distanceSquared = 0;
	frictionRasistance = 0;
}

GameBlock::GameBlock(float posX, float posY, float sizeX, float sizeY)
{
	SetPos(posX, posY, 0);
	SetSize(sizeX, sizeY, 0);
}

void GameBlock::Init()
{
	Initialize(L"Asset/pic/Box.png");   //�w�i��������
	//SetPos(groundX, groundY, 0.0f);      //�ʒu��ݒ�
	//SetSize(600.0f, 50.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�F��ݒ�
}

void GameBlock::Update(void)//����̃A�b�v�f�[�g
{
	float angle = GetAngle();
	if (angle < 30 && angle > -30)
	{
		angle += gyroData[1] * 0.75f;

		if (angle > 30)
		{
			angle = 29;
		}
		else if (angle < -30)
		{
			angle = -29;
		}

		SetAngle(angle);
	}
	
	if (Input::GetButtonTrigger(XINPUT_X))
	{
		SetAngle(0);
	}


	if (Input::GetKeyPress(VK_LEFT)) {
		SetAngle(GetAngle() + 3);
	}
	else if (Input::GetKeyPress(VK_RIGHT)) {
		SetAngle(GetAngle() - 3);
	}
	else if (Input::GetKeyPress(VK_SPACE)) {
		SetAngle(0);
	}
	float difAngle = GetAngle() - oldAngle;

	CorrectPointerPosition(difAngle);
	CorrectStonePosition(difAngle);
	CorrectSnowmanPosition(difAngle);

	oldAngle = GetAngle();
}

float GameBlock::GetFrictionRasistance()
{
	return frictionRasistance;
}

float GameBlock::GetOldAngle()
{
	return oldAngle;
}

void GameBlock::CorrectPointerPosition(float angle)
{
	std::vector<GamePointer*> pointers = Application::GetInstance()->GetObjects<GamePointer>();
	for (auto pointer : pointers) {
		collision = BoxCollider::ColliderWithCircle(pointer, this);
		if (collision.checkCollision != NO_COLLISION) {
			if (pointer->GetPos().x > GetPos().x && angle > 0 ||
				pointer->GetPos().x < GetPos().x && angle < 0) {
				Vector2 pos = { pointer->GetPos().x - GetPos().x , pointer->GetPos().y - GetPos ().y };

				pos.y = pos.x * sin(Math::ConvertToRadian(angle)) + pos.y * cos  (Math::ConvertToRadian(angle));

				pointer->SetPos(pointer->GetPos().x, GetPos().y + pos.y, 0);
			}
		}
	}
}

void GameBlock::CorrectStonePosition(float angle)
{
	std::vector<Stone*> stones = Application::GetInstance()->GetObjects<Stone>();
	for (auto stone : stones) {
		collision = BoxCollider::ColliderWithCircle(stone, this);
		if (collision.checkCollision != NO_COLLISION) {
			if (stone->GetPos().x > GetPos().x && angle > 0 ||
				stone->GetPos().x < GetPos().x && angle < 0) {
				Vector2 pos = { stone->GetPos().x - GetPos().x , stone->GetPos().y - GetPos().y };

				pos.y = pos.x * sin(Math::ConvertToRadian(angle)) + pos.y * cos(Math::ConvertToRadian(angle));

				stone->SetPos(stone->GetPos().x, GetPos().y + pos.y, 0);
			}
		}
	}
}

void GameBlock::CorrectSnowmanPosition(float angle)
{
	float difAngle = GetAngle() - oldAngle;
	std::vector<Snowman*> snowmans = Application::GetInstance()->GetObjects<Snowman>();
	for (auto snowman : snowmans) {
		collision = BoxCollider::ColliderWithCircle(snowman, this);
		if (collision.checkCollision != NO_COLLISION) {
			if (snowman->GetPos().x > GetPos().x && difAngle > 0 ||
				snowman->GetPos().x < GetPos().x && difAngle < 0) {
				Vector2 pos = { snowman->GetPos().x - GetPos().x , snowman->GetPos().y - GetPos().y };

				pos.y = pos.x * sin(Math::ConvertToRadian(difAngle)) + pos.y * cos(Math::ConvertToRadian(difAngle));

				snowman->SetPos(snowman->GetPos().x, GetPos().y + pos.y, 0);
			}
		}
	}
}
