#include "GameBlock.h"
#include "../../08_Collider/BoxCollider.h"
#include "../../03_GameMainFile/Game/GamePointer.h"
#include "../../03_GameMainFile/Application.h"
#include "../../03_GameMainFile/Game/Gimmick/Stone.h"
#include "../../03_GameMainFile/Game/Gimmick/Snowman.h"
#include "../Math.h"
#include <vector>
#include <cmath>
#include <limits>


extern float gyroData[3]; // x, y, z軸

float GameBlock::unificationFloorAngle = 0 ;
float GameBlock::unificationWallAngle  = 0 ;
bool  GameBlock::isCorrect = false ;





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
	oldMyBlock.SetPos(this->GetPos().x, this->GetPos().y, 0);
	oldMyBlock.SetAngle(this->GetAngle());

	vector<GamePointer*> pointers   = Application::GetInstance()->GetObjects<GamePointer>();
	vector<Stone*>		  stones    = Application::GetInstance()->GetObjects<Stone>();
	vector<Snowman*>	 snowmans   = Application::GetInstance()->GetObjects<Snowman>();
	vector<GameBlock*>	 gameBlocks = Application::GetInstance()->GetObjects<GameBlock>();

	bool myHit[8], otherHit[8], blockHit = false;
	for (int i = 0; i < 8; ++i)
	{
		myHit[i] = false;
		otherHit[i] = false;
	}
	int j = 0;

	//オブジェクトの確認
	for (auto block : gameBlocks) {
		if (block != this && blockHit == false) {
			if (BoxCollider::ColliderWithBox(block, this)) {
				blockHit = true;
				m_Block = block;
			}
		}
	}
	if (!blockHit) {
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
				if (myCollision.closspoint.pos.x == otherCollision[i].closspoint.pos.x &&
					myCollision.closspoint.pos.y == otherCollision[i].closspoint.pos.y) {
					myHit[j] = true;
				}
				else {
					otherHit[j] = true;
				}
				if(hitPoint != HIT_DOUBLE)
				{
					if (myHit[i] && otherHit[i])
					{
						hitPoint = HIT_DOUBLE;
						hitObject[j] = comparisonBlocks[i];
						j++;
					}
					else if (myHit[i]) 
					{
							hitPoint = HIT_ONE;
					}
				}			
			}
		}
		if (hitPoint != HIT_DOUBLE) {
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
				
				if (myCollision.closspoint.pos.x == otherCollision[i].closspoint.pos.x &&
					myCollision.closspoint.pos.y == otherCollision[i].closspoint.pos.y) {
					myHit[j] = true;
				}
				else {
					otherHit[j] = true;
				}
				if (hitPoint != HIT_DOUBLE)
				{
					if (myHit[i] && otherHit[i])
					{
						hitPoint = HIT_DOUBLE;
						hitObject[j] = comparisonBlocks[i];
						j++;
					}
					else if (myHit[i]) {
							hitPoint = HIT_ONE;
						
					}
				}
				
			}
		}
	}
	}

	if (!blockHit) {
		float angle = GetAngle();
		float bufAngle = gyroData[1] * 0.75f;
		angle += gyroData[1] * 0.75f;

		if (angle > 30)
		{
			angle = 29;
		}
		else if (angle < -30)
		{
			angle = -29;
		}
		if (hitPoint == HIT_DOUBLE) {
			CorrectAngle(myCollision, *hitObject[0]);
		}
		else {
			SetAngle(angle);
		}
		for (auto block : gameBlocks) {
			if (block != this && blockHit == false) {
				if (BoxCollider::ColliderWithBox(block, this)) {
					blockHit = true;
					m_Block = block;
					CorrectAngle(*this, *m_Block);
				}
			}
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

bool GameBlock::CheckCollision(Object& perBlock, Object& haveBlock, Vector2& mtv)
{
	Vector2 perHalfSize = { perBlock.GetSize().x / 2 ,perBlock.GetSize().y / 2 };
	Vector2 haveHalfSize = { haveBlock.GetSize().x / 2 ,haveBlock.GetSize().y / 2 };

	float angle = perBlock.GetAngle();
	Vector2  perAngle = { cos(angle) ,sin(angle)};
	angle = haveBlock.GetAngle();
	Vector2 haveAngle = { cos(angle) ,sin(angle) };

	Vector2 perHitCorner[4] = { { -perHalfSize.x * perAngle.x, - perHalfSize.y * perAngle.y},		//左下
								{  perHalfSize.x * perAngle.x, - perHalfSize.y * perAngle.y},		//右下
								{  perHalfSize.x * perAngle.x,   perHalfSize.y * perAngle.y},		//右上
								{ -perHalfSize.x * perAngle.x,   perHalfSize.y * perAngle.y} };		//左上

	Vector2 haveHitCorner[4] = { { -haveHalfSize.x * haveAngle.x, - haveHalfSize.y * haveAngle.y},		//左下
								 {  haveHalfSize.x * haveAngle.x, - haveHalfSize.y * haveAngle.y},		//右下
								 {  haveHalfSize.x * haveAngle.x,   haveHalfSize.y * haveAngle.y},		//右上
								 { -haveHalfSize.x * haveAngle.x,   haveHalfSize.y * haveAngle.y} };	//左上

	Vector2 axes[4] = { { perHitCorner[1].x -  perHitCorner[0].x , perHitCorner[0].y -  perHitCorner[0].y },
						{ perHitCorner[1].x -  perHitCorner[2].x , perHitCorner[1].y -  perHitCorner[1].y },
						{haveHitCorner[1].x - haveHitCorner[0].x ,haveHitCorner[2].y - haveHitCorner[2].y },
						{haveHitCorner[1].x - haveHitCorner[2].x ,haveHitCorner[3].y - haveHitCorner[3].y } };

	axes[0] = axes[0].Normalize();
	axes[1] = axes[1].Normalize();
	axes[2] = axes[2].Normalize();
	axes[3] = axes[3].Normalize();

	float minOverlap = 100000.0f;
	Vector2 smallestAxis;

	for (int i = 0; i < 4; ++i) {
		float min1 = Math::dot(axes[i], perHitCorner[0]);
		float max1 = min1;
		for (int j = 0; j < 4; ++j ){
			float projection = Math::dot(axes[i], perHitCorner[i]);
			min1 = min(min1, projection);
			max1 = max(max1, projection);
		}

		float min2 = Math::dot(axes[i], haveHitCorner[0]);
		float max2 = min2;
		for (int j = 0; j < 4; ++j) {
			float projection = Math::dot(axes[i], haveHitCorner[i]);
			min1 = min(min1, projection);
			max1 = max(max1, projection);
		}

		if (max1 < min2 || max2 < min1) {
			return false; // 衝突していない
		}

		float overlap = min(max1, max2) - max(min1, min2);
		if (overlap < minOverlap) {
			minOverlap = overlap;
			smallestAxis = axes[i];
		}
	}

	mtv = { smallestAxis.x * minOverlap, smallestAxis.y * minOverlap };
	return true; // 衝突している
}


void GameBlock::CorrectPointerPosition(float angle)
{
	std::vector<GamePointer*> pointers = Application::GetInstance()->GetObjects<GamePointer>();
	for (auto pointer : pointers) {
		myCollision = BoxCollider::ColliderWithCircle(pointer, this);
		if (myCollision.checkCollision != NO_COLLISION) {
			if (pointer->GetPos().x > GetPos().x && angle > 0.0f ||
				pointer->GetPos().x < GetPos().x && angle < 0.0f) {
				Vector2 pos = { pointer->GetPos().x - GetPos().x , pointer->GetPos().y - GetPos ().y };

				pos.y = pos.x * sin(Math::ConvertToRadian(angle)) + pos.y * cos  (Math::ConvertToRadian(angle));

				pointer->SetPos(pointer->GetPos().x, GetPos().y + pos.y, 0.0f);
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
			if (stone->GetPos().x > GetPos().x && angle > 0.0f ||
				stone->GetPos().x < GetPos().x && angle < 0.0f) {
				Vector2 pos = { stone->GetPos().x - GetPos().x , stone->GetPos().y - GetPos().y };

				pos.y = pos.x * sin(Math::ConvertToRadian(angle)) + pos.y * cos(Math::ConvertToRadian(angle));

				stone->SetPos(stone->GetPos().x, GetPos().y + pos.y, 0.0f);
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

			snowman->SetPos(GetPos().x + pos.x, GetPos().y + pos.y, 0.0f);
			snowman->SetAngle(GetAngle());
			
		}
	}
}
void GameBlock::CorrectAngle(ContactPointVector collision, Object pointer)
{
	// 接地点から円の中心へのベクトルを計算
	Vector2 normal = { pointer.GetPos().x - collision.closspoint.pos.x , pointer.GetPos().y - collision.closspoint.pos.y };

	//法線ベクトルの角度
	Radian nrmAngleR = Math::NormalizeRadian(atan2(normal.y, normal.x));	//0~360に正規化		
	Degree nrmAngleD = Math::ConvertToDegree((nrmAngleR));

	switch (collision.checkCollision) {
	case LEFTUP:	nrmAngleR = Math::ConvertToRadian(clamp(nrmAngleD,  90.0f + GetAngle(), 180.0f + GetAngle())); break;
	case LEFTDOWN:	nrmAngleR = Math::ConvertToRadian(clamp(nrmAngleD, 180.0f + GetAngle(), 270.0f + GetAngle())); break;
	case RIGHTUP:	nrmAngleR = Math::ConvertToRadian(clamp(nrmAngleD,   0.0f + GetAngle(),  90.0f + GetAngle())); break;
	case RIGHTDOWN: nrmAngleR = Math::ConvertToRadian(clamp(nrmAngleD, 270.0f + GetAngle(), 360.0f + GetAngle())); break;
	}

	//面の中心座標
	Vector2 clossSurfacePos;
	float distanceCorrect = (pointer.GetSize().x / 2.0f) - sqrt(collision.distanceSquared);

	clossSurfacePos.x = GetPos().x + (GetSize().y / 2.0f * cos(nrmAngleR));
	clossSurfacePos.y = GetPos().y + (GetSize().y / 2.0f * sin(nrmAngleR));

	Vector2 distanceCtoS = { clossSurfacePos.x - collision.closspoint.pos.x ,
							 clossSurfacePos.y - collision.closspoint.pos.y };

	if (distanceCtoS.x < 0.0f) { distanceCtoS.x *= - 1.0f ; }
	if (distanceCtoS.y < 0.0f) { distanceCtoS.y *= - 1.0f ; }

	float distanceCtoSNum = distanceCtoS.Length();
	Radian correctAngleR = atan2(distanceCorrect, distanceCtoSNum);
	Degree correctAngleD = Math::ConvertToDegree(correctAngleR) + 0.1f;

	//第１象限と第３象限
	if (nrmAngleD <= 0.0f && nrmAngleD >= 90.0f ||
		nrmAngleD >= 270.0f && nrmAngleD <= 360.0f) {
		correctAngleD *= - 1.0f;
	}

	SetAngle(GetAngle() + correctAngleD);
}
void GameBlock::CorrectAngle(Object& perBlock, Object& haveBlock)//加害者と被害者
{
	Vector2 mtv;
	float angleStep = 0.01f; // 角度の調整ステップ（ラジアン単位）
	int maxIterations = 1000; // 最大反復回数

	for (int i = 0; i < maxIterations; ++i) {
		if (!CheckCollision(perBlock, haveBlock, mtv)) {
			return; // 衝突が解消された
		}
		perBlock.SetAngle(perBlock.GetAngle() + angleStep); // 角度を調整
	}

}

void GameBlock::CorrectBlockPosition(Object& perBlock, Object& haveBlock)
{
	if (CheckCollision(perBlock, haveBlock, mtv)) {
		perBlock.SetPos(perBlock.GetPos().x - mtv.x, perBlock.GetPos().y - mtv.y, 0.0f);
	}
}
