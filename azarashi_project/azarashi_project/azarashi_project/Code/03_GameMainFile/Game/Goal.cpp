#include "Goal.h"
#include "GamePointer.h"
#include"../Application.h"
#include "../../08_Collider/BoxCollider.h"
#include <vector>
void Goal::Init()
{
	//SetTexture(textures[0]);
	Initialize(L"Asset/pic/Goal.PNG");   //�w�i��������
	//SetPos(0.0f, 448.0f, 0.0f);      //�ʒu��ݒ�
	SetSize(128.0f, 128.0f, 0.0f);  //�傫����ݒ�
	SetAngle(0.0f);                //�p�x��ݒ�
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�p�x��ݒ�
}

void Goal::Update()//�w�i�̃A�b�v�f�[�g(����Ȃ��C������)
{
	std::vector<GamePointer*> Player = Application::GetInstance()->GetObjects<GamePointer>();
	for (auto& Player1 : Player)
	{
		if (isGoalAchieved)
		{

		}
		else
		{
			//Goal* self = this;
			DirectX::XMFLOAT3 pos_Player = Player1->GetPos();
			DirectX::XMFLOAT3 size_Player = Player1->GetSize();

			DirectX::XMFLOAT3 pos_Goal = GetPos();
			DirectX::XMFLOAT3 size_Goal = GetSize();

			/*if (pos_Goal.y == 0)
			{
				int i = 1;
			}*/
			
			//�A�U���V�Ƃ̓����蔻��
			double halfWidth1  = size_Player.x  / 3.0;
			double halfHeight1 = size_Player.y  / 3.0;
			double halfWidth2  = size_Goal.x  / 3.0;
			double halfHeight2 = size_Goal.y  / 3.0;

			if (pos_Player.x - halfWidth1 < pos_Goal.x + halfWidth2 &&
				pos_Player.x + halfWidth1 > pos_Goal.x - halfWidth2 &&
				pos_Player.y - halfHeight1 < pos_Goal.y + halfHeight2 &&
				pos_Player.y + halfHeight1 > pos_Goal.y - halfHeight2)//Goal�ɓ������Ă�����c
			{

				isGoalAchieved = true;//�������Ă���ɕς��܂�
			}
		}
		
	}	
}

