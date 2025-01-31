#include "GameBlock.h"
#include "../../08_Collider/BoxCollider.h"
#include "../../03_GameMainFile/Game/GamePointer.h"
#include "../../03_GameMainFile/Application.h"
#include "../../03_GameMainFile/Game/Gimmick/Stone.h"
#include "../../03_GameMainFile/Game/Gimmick/Snowman.h"
#include <vector>

extern float gyroData[3]; // x, y, z軸

GameBlock::GameBlock()
{
	myCollision.checkCollision = NO_COLLISION;
	myCollision.closspoint = { -1,-1 };
	myCollision.distanceSquared = 0;
	frictionRasistance = 0;
	for (int i = 0; i < 2; ++i) {
		otherCollision[i].checkCollision = NO_COLLISION;
		otherCollision[i].closspoint = { -1,-1 };
		otherCollision[i].distanceSquared = 0;
		hitObject[i] = nullptr;
	}
}

GameBlock::GameBlock(float posX, float posY, float sizeX, float sizeY)
{
	SetPos(posX, posY, 0);
	SetSize(sizeX, sizeY, 0);
}

void GameBlock::Init()
{
	Initialize(L"Asset/pic/Box.png");   //背景を初期化
	//SetPos(groundX, groundY, 0.0f);      //位置を設定
	//SetSize(600.0f, 50.0f, 0.0f);  //大きさを設定
	SetAngle(0.0f);                //角度を設定
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//色を設定
}

void GameBlock::Update(void)//足場のアップデート
{
	vector<GamePointer*> pointers = Application::GetInstance()->GetObjects<GamePointer>();
	vector<Stone*>		  stones  = Application::GetInstance()->GetObjects<Stone>();
	vector<Snowman*>	 snowmans = Application::GetInstance()->GetObjects<Snowman>();

	size_t sizeCast = pointers.size() + stones.size() + snowmans.size();
	int objSize = static_cast<int>(sizeCast);
	bool myHit[8], otherHit[8], blockHit = false;
	for (int i = 0; i < 8; ++i)
	{
		myHit[i] = false;
		otherHit[i] = false;
	}
	int j = 0;

	for (auto pointer : pointers) {
		myCollision = BoxCollider::ColliderWithCircle(pointer, this);
		Object* comparisonBlocks[2];
		for (int i = 0; i < 2; ++i) {
			comparisonBlocks[i] = pointer->GetHitGameBlock(i);
			if (comparisonBlocks[i] != nullptr) {
				otherCollision[i] = BoxCollider::ColliderWithCircle(pointer, comparisonBlocks[i]);
			}else {
				otherCollision[i].checkCollision = NO_COLLISION;
				otherCollision[i].closspoint = { -1,-1 };
				otherCollision[i].distanceSquared = -1;
			}
			if (myCollision.closspoint.x == otherCollision[i].closspoint.x &&
				myCollision.closspoint.y == otherCollision[i].closspoint.y) {
				myHit[j] = true;
			}
			else {
				otherHit[j] = true;
			}
			if(hitPoint != DOUBLE_HITS)
			{
				if (myHit[i] && otherHit[i])
				{
					hitPoint = DOUBLE_HITS;
					hitObject[j] = comparisonBlocks[i];
					j++;
				}
				else if (myHit[i]) 
				{
						hitPoint = MY_ONLY;
				}
			}			
		}
	}
	if (hitPoint != DOUBLE_HITS) {
		for (auto stone : stones) {
			myCollision = BoxCollider::ColliderWithCircle(stone, this);
			Object* comparisonBlocks[2];
			for (int i = 0; i < 2; ++i) 
			{
				comparisonBlocks[i] = stone->GetHitGameBlock(i);
				if (comparisonBlocks[i] != nullptr) {
					otherCollision[i] = BoxCollider::ColliderWithCircle(stone, comparisonBlocks[i]);
				}
				else {
					otherCollision[i].checkCollision = NO_COLLISION;
					otherCollision[i].closspoint = { -1,-1 };
					otherCollision[i].distanceSquared = -1;
				}
				
				if (myCollision.closspoint.x == otherCollision[i].closspoint.x &&
					myCollision.closspoint.y == otherCollision[i].closspoint.y) {
					myHit[j] = true;
				}
				else {
					otherHit[j] = true;
				}
				if (hitPoint != DOUBLE_HITS)
				{
					if (myHit[i] && otherHit[i])
					{
						hitPoint = DOUBLE_HITS;
						hitObject[j] = comparisonBlocks[i];
						j++;
					}
					else if (myHit[i]) {
							hitPoint = MY_ONLY;
						
					}
				}
				
			}
		}
	}

	float angle = GetAngle();
	float bufAngle = gyroData[1] * 0.75f;
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
		if (hitPoint == DOUBLE_HITS) {
			CorrectAngle(myCollision, *hitObject[0]);
		}
		else {
			SetAngle(angle);
		}
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
	/*else if (Input::GetKeyPress(VK_SPACE)) {
		SetAngle(0);
	}*/
	float difAngle = gyroData[1] * 0.75f;

	CorrectPointerPosition(difAngle);
	CorrectStonePosition(difAngle);
	CorrectSnowmanPosition(difAngle);


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
		myCollision = BoxCollider::ColliderWithCircle(pointer, this);
		if (myCollision.checkCollision != NO_COLLISION) {
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
		myCollision = BoxCollider::ColliderWithCircle(stone, this);
		if (myCollision.checkCollision != NO_COLLISION) {
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
		myCollision = BoxCollider::ColliderWithCircle(snowman, this);
		if (myCollision.checkCollision != NO_COLLISION) {
			Vector2 pos = { snowman->GetPos().x - GetPos().x , snowman->GetPos().y - GetPos().y };

			pos.x = pos.x * cos(Math::ConvertToRadian(difAngle)) - pos.y * sin(Math::ConvertToRadian(difAngle));
			pos.y = pos.x * sin(Math::ConvertToRadian(difAngle)) + pos.y * cos(Math::ConvertToRadian(difAngle));

			snowman->SetPos(GetPos().x + pos.x, GetPos().y + pos.y, 0);
			snowman->SetAngle(GetAngle());
			
		}
	}
}

void GameBlock::CorrectAngle(ContactPointVector collision, Object pointer)
{
	// 接地点から円の中心へのベクトルを計算
	Vector2 normal = { pointer.GetPos().x - collision.closspoint.x , pointer.GetPos().y - collision.closspoint.y };

	//法線ベクトルの角度
	Radian nrmAngleR = Math::NormalizeRadian(atan2(normal.y, normal.x));	//0~360に正規化		
	Degree nrmAngleD = Math::ConvertToDegree((nrmAngleR));

	switch (collision.checkCollision) {
	case LEFTUP:	nrmAngleR = Math::ConvertToRadian(clamp(nrmAngleD, 90 + GetAngle(), 180 + GetAngle())); break;
	case LEFTDOWN:	nrmAngleR = Math::ConvertToRadian(clamp(nrmAngleD, 180 + GetAngle(), 270 + GetAngle())); break;
	case RIGHTUP:	nrmAngleR = Math::ConvertToRadian(clamp(nrmAngleD, 0 + GetAngle(), 90 + GetAngle())); break;
	case RIGHTDOWN: nrmAngleR = Math::ConvertToRadian(clamp(nrmAngleD, 270 + GetAngle(), 360 + GetAngle())); break;
	}

	//面の中心座標
	Vector2 clossSurfacePos;
	float distanceCorrect = (pointer.GetSize().x / 2) - sqrt(collision.distanceSquared);

	clossSurfacePos.x = GetPos().x + (GetSize().y / 2 * cos(nrmAngleR));
	clossSurfacePos.y = GetPos().y + (GetSize().y / 2 * sin(nrmAngleR));

	Vector2 distanceCtoS = { clossSurfacePos.x - collision.closspoint.x ,
							 clossSurfacePos.y - collision.closspoint.y };

	if (distanceCtoS.x < 0) { distanceCtoS.x *= -1; }
	if (distanceCtoS.y < 0) { distanceCtoS.y *= -1; }

	float distanceCtoSNum = distanceCtoS.Length();
	Radian correctAngleR = atan2(distanceCorrect, distanceCtoSNum);
	Degree correctAngleD = Math::ConvertToDegree(correctAngleR) + 0.1;

	//第１象限と第３象限
	if (nrmAngleD <= 0 && nrmAngleD >= 90 ||
		nrmAngleD >= 270 && nrmAngleD <= 360) {
		correctAngleD *= -1;
	}

	SetAngle(GetAngle() + correctAngleD);
}
