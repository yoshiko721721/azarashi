#include "BoxCollider.h"
#include <algorithm>


//--------------------------------------------------------------
//�X���ɍ��킹�Ē����`�̊p�x�v�Z�֐�(��]���W)
// //2024/11/14 ���]
//--------------------------------------------------------------
DirectX::XMFLOAT2 BoxCollider::RotatePosition(/*��`�̒��S���W*/DirectX::XMFLOAT2 point, /*��`�̊p�x*/float angle)
{
    DirectX::XMFLOAT2 result;
    result.x = point.x * cos(angle) - point.y * sin(angle);//��]�s����g����X���W��ύX�����
    result.y = point.x * sin(angle) + point.y * cos(angle);//��]�s����g����Y���W��ύX����� 
    return result;
}


//--------------------------------------------------------------
//�~�Ǝl�p�̓����蔻��֐�
//2024/12/11 ���]
//--------------------------------------------------------------

ContactPointVector BoxCollider::ColliderWithCircle(Object* p_Circle, Object* p_Box)
{
    TransForm box;
    TransForm circle;

    box.TransFormInitialize(*p_Box);
    circle.TransFormInitialize(*p_Circle);

    DirectX::XMFLOAT2 normalizedVector = { 0.0f,0.0f };
    DirectX::XMFLOAT2 closestPoint     = { 0.0f,0.0f };

    // �e�ӂƉ~�Ƃ̋����𔻒�
    for (int i = 0; i < 4; i++)
    {
        DirectX::XMFLOAT2 p1 = box.vertex[i];
        DirectX::XMFLOAT2 p2 = box.vertex[(i + 1) % 4];

        // �ӂ̕����x�N�g��
        DirectX::XMFLOAT2 edge = { p2.x - p1.x, p2.y - p1.y };//�p����p�̃x�N�g����}���
        DirectX::XMFLOAT2 toCircle = { circle.position.x - p1.x, circle.position.y - p1.y };//�_����p�̃x�N�g����}���

        float t = fmax(0, fmin(1, (toCircle.x * edge.x + toCircle.y * edge.y) / (edge.x * edge.x + edge.y * edge.y)));
        closestPoint = { p1.x + t * edge.x, p1.y + t * edge.y }; //�Ԃ��l

        // �ŋߐړ_�Ɖ~�̒��S�̋������v�Z
        float distanceSquared = (closestPoint.x - circle.position.x) * (closestPoint.x - circle.position.x) + (closestPoint.y - circle.position.y) * (closestPoint.y - circle.position.y);//�Ԃ��l
        float radius = circle.halfSize.y;
        if (distanceSquared <= radius * radius)
        {
            float clossPointNum = Math::CalcSquareRoot(closestPoint.x, closestPoint.y);
            for (int j = 0; j < 4; ++j) {
                float hitCornerNum = Math::CalcSquareRoot(box.vertex[j].x, box.vertex[j].y);
                float distanceNum = clossPointNum - hitCornerNum;
                if (distanceNum < 0.0001 && distanceNum > -0.0001) {
                    switch (j) {
                    case 0: return{ LEFTDOWN  , (closestPoint, 0.0f) , distanceSquared };     break;
                    case 1: return{ RIGHTDOWN , (closestPoint, 0.0f) , distanceSquared };     break;
                    case 2: return{ RIGHTUP   , (closestPoint, 0.0f) , distanceSquared };     break;
                    case 3: return{ LEFTUP    , (closestPoint, 0.0f) , distanceSquared };     break;
                    }
                }
            }
            
            Radian nrmAngleR = atan2(edge.y, edge.x) + M_PI / 2.0f ;
            return { COLLISION, (closestPoint, 0.0f) ,distanceSquared };

        }
    }
    return { NO_COLLISION, (closestPoint, 0.0f) , -1 };
};
//--------------------------------------------------------------
//�l�p�Ǝl�p�̓����蔻��֐�
//2024/12/03 ���]
//--------------------------------------------------------------
bool BoxCollider::ColliderWithBox(Object* p_Box1, Object* p_Box2)
{
    DirectX::XMFLOAT2 hitcorners2[4] = {//�����蔻����Ƃ�ۂ̍��W�i�[��
        { 0, 0 }, //LeftBottom
        { 0, 0 }, //RightBottom
        { 0, 0 }, //RightTop
        { 0, 0 }, //LeftTop
    };

    float angle1 = p_Box1->GetAngle();
    angle1 = angle1 * (M_PI / 180.0);   //�p�x�����W�A���ɕϊ�
    
    DirectX::XMFLOAT3 boxpos1 = p_Box1->GetPos();   //�|�C���^�[���g����Box�̍��W�擾
    DirectX::XMFLOAT3 boxsize1 = p_Box1->GetSize();  //�|�C���^�[���g����circle�̃T�C�Y�擾

//-------------------�����蔻��������Ă�����̋�`�v�Z--------------------------------
    //��`�̕��ƍ����𔼕��ɂ��Ă������Ƃō��W�v�Z���ȒP�ɂȂ�
    DirectX::XMFLOAT2 halfsize1 = { boxsize1.x / 2,boxsize1.y / 2 };//OK
    DirectX::XMFLOAT2 hitcorners[4];
    //���̔����ƍ����̔����̐��l���g���Ē����`�̒��_�̍��W���v�Z����(o^�\^o)
    hitcorners[0] = { -halfsize1.x , -halfsize1.y };
    hitcorners[1] = {  halfsize1.x , -halfsize1.y };
    hitcorners[2] = {  halfsize1.x ,  halfsize1.y };
    hitcorners[3] = { -halfsize1.x ,  halfsize1.y };//OK

    //��]��A���s�ړ���̍��W�ɕϊ�(�l�p���ׂ�)
    for (int i = 0; i < 4; i++) {
        hitcorners[i] = RotatePosition(hitcorners[i], angle1);//�����`�̊e�p����]������
        hitcorners[i].x += boxpos1.x;//�ϊ�������`��X�ɋ�`�̒��S���WX�𑫂�
        hitcorners[i].y += boxpos1.y;//�ϊ�������`��Y�ɋ�`�̒��S���WY�𑫂�

    }//OK

    DirectX::XMFLOAT2 edge[4];//�x�N�g����ۑ�����z��ł�

    for (int i = 0; i < 4; i++)//�S�Ă̕ӂ̃x�N�g�����v�Z����for��
    {
        DirectX::XMFLOAT2 p1 = hitcorners[i];
        DirectX::XMFLOAT2 p2 = hitcorners[(i + 1) % 4];
        // �ӂ̕����x�N�g��
        edge[i] = { p2.x - p1.x, p2.y - p1.y };//�p����p�̃x�N�g����}���
    }

//----------------------------------------------------------------------------------------
    float angle2 = p_Box2->GetAngle();
    angle2 = angle2 * (M_PI / 180.0);

    DirectX::XMFLOAT3 boxpos2 = p_Box2->GetPos();   //�|�C���^�[���g����Box�̍��W�擾
    DirectX::XMFLOAT3 boxsize2 = p_Box2->GetSize();  //�|�C���^�[���g����circle�̃T�C�Y�擾

     //��`�̕��ƍ����𔼕��ɂ��Ă������Ƃō��W�v�Z���ȒP�ɂȂ�
    DirectX::XMFLOAT2 halfsize2 = { boxsize2.x / 2 , boxsize2.y / 2};//OK

     //���̔����ƍ����̔����̐��l���g���Ē����`�̒��_�̍��W���v�Z����(o^�\^o)
    hitcorners2[0] = { -halfsize2.x , -halfsize2.y };
    hitcorners2[1] = {  halfsize2.x , -halfsize2.y };
    hitcorners2[2] = {  halfsize2.x ,  halfsize2.y };
    hitcorners2[3] = { -halfsize2.x ,  halfsize2.y };//OK

    //��]��A���s�ړ���̍��W�ɕϊ�(�l�p���ׂ�)
    for (int i = 0; i < 4; i++) {
        hitcorners2[i] = RotatePosition(hitcorners2[i], angle1);//�����`�̊e�p����]������
        hitcorners2[i].x += boxpos2.x;//�ϊ�������`��X�ɋ�`�̒��S���WX�𑫂�
        hitcorners2[i].y += boxpos2.y;//�ϊ�������`��Y�ɋ�`�̒��S���WY�𑫂�

    }//OK
 //----------------------------------------------------------------------------------------
    DirectX::XMFLOAT2 relative_position;
    DirectX::XMFLOAT2 transform_pos;

     for(int i = 0;i < 4;i++)
     {
        //�p�̑��΍��W�����o��
         float slope1 = (hitcorners[(i + 1) % 4].y - hitcorners[i].y) / (hitcorners[(i + 1) % 4].x - (hitcorners[i].x + 0.0001));

        for (int j = 0; j < 4; j++)
        {
            float slope2 = (hitcorners2[(j + 1) % 4].y - hitcorners2[j].y) / (hitcorners2[(j + 1) % 4].x - (hitcorners2[j].x + 0.0001));
            if (slope1 != slope2)
            {
                DirectX::XMFLOAT2 crossPoint;
                crossPoint.x = (hitcorners2[j].y - hitcorners[i].y + slope1 * hitcorners[i].x - slope2 * hitcorners2[j].x) / (slope1 - slope2);
                crossPoint.y = slope1 * (crossPoint.x - hitcorners[i].x) + hitcorners[i].y;

                float r0 = (crossPoint.x -  hitcorners[i].x) / (hitcorners[(i + 1) % 4].x - hitcorners[i].x);//�����͈̔͂����߂�(���ꑤ
                float r1 = (crossPoint.x - hitcorners2[j].x) / (hitcorners2[(j + 1) % 4].x - hitcorners2[j].x - 0.0001);//�����͈̔͂����߂�(�����Ă���Box��)

                if (r0 <= 1 && r0 >= 0 && r1 <= 1 && r1 >= 0)
                {
                    return true;
                }
            }
        }
        
     }

    return false;
}
//--------------------------------------------------------------
//�͈͓���circle���Ȃɂ����邩�ǂ����𒲂ׂ�֐�
//2024/11/23 ���]
//--------------------------------------------------------------
//bool BoxCollider::IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height){}



