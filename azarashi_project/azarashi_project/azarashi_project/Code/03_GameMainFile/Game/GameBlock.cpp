#include "GameBlock.h"
#include "../../08_Collider/BoxCollider.h"
#include "../../03_GameMainFile/Game/GamePointer.h"
#include "../../03_GameMainFile/Application.h"
#include <vector>

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
	SetPos(groundX, groundY, 0.0f);      //�ʒu��ݒ�
	SetSize(600.0f, 50.0f, 0.0f);  //�傫����ݒ�
	SetAngle(90.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�F��ݒ�
}

void GameBlock::Update(void)//����̃A�b�v�f�[�g
{
	if (Input::GetKeyPress(VK_LEFT)) {
		SetAngle(GetAngle() + 3);
	}
	else if (Input::GetKeyPress(VK_RIGHT)) {
		SetAngle(GetAngle() - 3);
	}
	else if (Input::GetKeyPress(VK_SPACE)) {
		SetAngle(0);
	}

}

float GameBlock::GetFrictionRasistance()
{
	return frictionRasistance;
}

void GameBlock::CorrectPointerPosition()
{
	float difAngle = GetAngle() - oldAngle;
	std::vector<GamePointer*> pointers = Application::GetInstance()->GetObjects<GamePointer>();
	for (auto pointer : pointers) {
		collision = BoxCollider::ColliderWithCircle(pointer, this);
		if (collision.checkCollision != NO_COLLISION) {
			if (pointer->GetPos().x > GetPos().x && difAngle > 0 ||
				pointer->GetPos().x < GetPos().x && difAngle < 0) {
				Vector2 pos = { pointer->GetPos().x - GetPos().x , pointer->GetPos().y - GetPos ().y };

				pos.x = pos.x * cos(Math::ConvertToRadian(difAngle)) - pos.y * sin  (Math::ConvertToRadian(difAngle));
				pos.y = pos.x * sin(Math::ConvertToRadian(difAngle)) + pos.y * cos  (Math::ConvertToRadian(difAngle));

				pointer->SetPos(GetPos().x + pos.x, GetPos().y + pos.y, 0);
			}
		}
	}

	oldAngle = GetAngle();
}
