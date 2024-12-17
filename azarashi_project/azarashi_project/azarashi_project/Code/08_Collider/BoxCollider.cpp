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

// �x�N�g���̓��ς��v�Z 
float BoxCollider::dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2)
{ 
    return v1.x * v2.x + v1.y * v2.y; 
}

//--------------------------------------------------------------
//�~�Ǝl�p�̓����蔻��֐�
//2024/12/11 ���]
//--------------------------------------------------------------

ContactPointVector BoxCollider::ColliderWithCircle(Object* m_GamePlayer, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height)
{
    angle = angle * (M_PI / 180.0);   //�p�x�����W�A���ɕϊ�

    DirectX::XMFLOAT3 circlepos = m_GamePlayer->GetPos();   //�|�C���^�[���g����circle�̍��W�擾
    DirectX::XMFLOAT2 circlepos2 = { circlepos.x,circlepos.y };
    DirectX::XMFLOAT3 circlesize =m_GamePlayer->GetSize();  //�|�C���^�[���g����circle�̃T�C�Y�擾

    //��`�̕��ƍ����𔼕��ɂ��Ă������Ƃō��W�v�Z���ȒP�ɂȂ�
    DirectX::XMFLOAT2 halfsize = { wihtd / 2,height / 2 };//OK

    //���̔����ƍ����̔����̐��l���g���Ē����`�̒��_�̍��W���v�Z����(o^�\^o)
    hitcorners[0] = { -halfsize.x , -halfsize.y };
    hitcorners[1] = {  halfsize.x , -halfsize.y };
    hitcorners[2] = {  halfsize.x ,  halfsize.y };
    hitcorners[3] = { -halfsize.x ,  halfsize.y };//OK

    //��]��A���s�ړ���̍��W�ɕϊ�(�l�p���ׂ�)
    for (int i = 0; i < 4; i++) {
        hitcorners[i] = RotatePosition(hitcorners[i], angle);//�����`�̊e�p����]������
        hitcorners[i].x += Scaffoldposx;//�ϊ�������`��X�ɋ�`�̒��S���WX�𑫂�
        hitcorners[i].y += Scaffoldposy;//�ϊ�������`��Y�ɋ�`�̒��S���WY�𑫂�
       
    }//OK

    DirectX::XMFLOAT2 normalizedVector = {0.0f,0.0f};
    DirectX::XMFLOAT2 closestPoint = { 0.0f,0.0f };

     // �e�ӂƉ~�Ƃ̋����𔻒�
    for(int i = 0; i < 4; i++)
    {
        DirectX::XMFLOAT2 p1 = hitcorners[i];
        DirectX::XMFLOAT2 p2 = hitcorners[(i + 1) % 4];

        // �ӂ̕����x�N�g��
        DirectX::XMFLOAT2 edge = { p2.x - p1.x, p2.y - p1.y };//�p����p�̃x�N�g����}���
        DirectX::XMFLOAT2 toCircle = { circlepos.x - p1.x, circlepos.y - p1.y };//�_����p�̃x�N�g����}���

        float t = fmax(0, fmin(1, (toCircle.x * edge.x + toCircle.y * edge.y) / (edge.x * edge.x + edge.y * edge.y)));
        closestPoint = { p1.x + t * edge.x, p1.y + t * edge.y }; //�Ԃ��l

        // �ŋߐړ_�Ɖ~�̒��S�̋������v�Z
        float distanceSquared = (closestPoint.x - circlepos.x) * (closestPoint.x - circlepos.x) + (closestPoint.y - circlepos.y) * (closestPoint.y - circlepos.y);//�Ԃ��l
        // ���������a�ȉ��Ȃ瓖����Ɣ���
        if (distanceSquared <= circlesize.y / 2 * circlesize.y / 2)
        {
            DirectX::XMFLOAT2 vectorToCenter = { closestPoint.x - circlepos.x , closestPoint.y - circlepos.y };
            float length = sqrt(vectorToCenter.x * vectorToCenter.x + vectorToCenter.y * vectorToCenter.y); 
           normalizedVector = { vectorToCenter.x / length, vectorToCenter.y / length };
            //closscircle = closestPoint;
            //distancesquared = distanceSquared;

            return { true, closestPoint ,normalizedVector };

        }
    }
    return { false, closestPoint ,normalizedVector };
};
//--------------------------------------------------------------
//�l�p�Ǝl�p�̓����蔻��֐�
//2024/12/03 ���]
//--------------------------------------------------------------
bool BoxCollider::ColliderWithBox(Object* m_GamePlayer, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height, DirectX::XMFLOAT2& touchbox)
{
    DirectX::XMFLOAT2 hitcorners2[4] = {//�����蔻����Ƃ�ۂ̍��W�i�[��
        { 0, 0 }, //LeftBottom
        { 0, 0 }, //RightBottom
        { 0, 0 }, //RightTop
        { 0, 0 }, //LeftTop
    };

    angle = angle * (M_PI / 180.0);   //�p�x�����W�A���ɕϊ�
    float angle1 = m_GamePlayer->GetAngle();
    angle1 = angle1 * (M_PI / 180.0);

    DirectX::XMFLOAT3 boxpos = m_GamePlayer->GetPos();   //�|�C���^�[���g����Box�̍��W�擾
    DirectX::XMFLOAT2 boxpos2 = { boxpos.x,boxpos.y };
    DirectX::XMFLOAT3 boxsize = m_GamePlayer->GetSize();  //�|�C���^�[���g����circle�̃T�C�Y�擾

//-------------------�����蔻��������Ă�����̋�`�v�Z--------------------------------
    //��`�̕��ƍ����𔼕��ɂ��Ă������Ƃō��W�v�Z���ȒP�ɂȂ�
    DirectX::XMFLOAT2 halfsize1 = { wihtd / 2,height / 2 };//OK

    //���̔����ƍ����̔����̐��l���g���Ē����`�̒��_�̍��W���v�Z����(o^�\^o)
    hitcorners[0] = { -halfsize1.x , -halfsize1.y };
    hitcorners[1] = {  halfsize1.x , -halfsize1.y };
    hitcorners[2] = {  halfsize1.x ,  halfsize1.y };
    hitcorners[3] = { -halfsize1.x ,  halfsize1.y };//OK

    //��]��A���s�ړ���̍��W�ɕϊ�(�l�p���ׂ�)
    for (int i = 0; i < 4; i++) {
        hitcorners[i] = RotatePosition(hitcorners[i], angle);//�����`�̊e�p����]������
        hitcorners[i].x += Scaffoldposx;//�ϊ�������`��X�ɋ�`�̒��S���WX�𑫂�
        hitcorners[i].y += Scaffoldposy;//�ϊ�������`��Y�ɋ�`�̒��S���WY�𑫂�

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

     //��`�̕��ƍ����𔼕��ɂ��Ă������Ƃō��W�v�Z���ȒP�ɂȂ�
    DirectX::XMFLOAT2 halfsize2 = { boxsize.x / 2 , boxsize.y / 2};//OK

     //���̔����ƍ����̔����̐��l���g���Ē����`�̒��_�̍��W���v�Z����(o^�\^o)
    hitcorners2[0] = { -halfsize2.x , -halfsize2.y };
    hitcorners2[1] = {  halfsize2.x , -halfsize2.y };
    hitcorners2[2] = {  halfsize2.x ,  halfsize2.y };
    hitcorners2[3] = { -halfsize2.x ,  halfsize2.y };//OK

    //��]��A���s�ړ���̍��W�ɕϊ�(�l�p���ׂ�)
    for (int i = 0; i < 4; i++) {
        hitcorners2[i] = RotatePosition(hitcorners2[i], angle1);//�����`�̊e�p����]������
        hitcorners2[i].x += boxpos.x;//�ϊ�������`��X�ɋ�`�̒��S���WX�𑫂�
        hitcorners2[i].y += boxpos.y;//�ϊ�������`��Y�ɋ�`�̒��S���WY�𑫂�

    }//OK
 //----------------------------------------------------------------------------------------
    DirectX::XMFLOAT2 relative_position;
    DirectX::XMFLOAT2 transform_pos;
    /*for (int i = 0; i < 4; i++)
    {
        //�p�̑��΍��W�����o��
        relative_position = { hitcorners2[i].x - Scaffoldposx , hitcorners2[i].y - Scaffoldposy };

        //���΍��W�ɑ΂��ċ�`�̉�]��ł������t�s����|����
        transform_pos = { cos(angle) * relative_position.x + sin(angle) * relative_position.y ,-sin(angle) * relative_position.x + cos(angle) * relative_position.y };

         // ��`�Ɠ_�̓����蔻����s��
        if (-halfsize1.x <= transform_pos.x && halfsize1.x >= transform_pos.x && -halfsize1.y <= transform_pos.y && halfsize1.y >= transform_pos.y)
        {
            return true;
        }
    }*/

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
bool BoxCollider::IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height)
{
    // ��`�̒��S����~�̒��S�܂ł̋������v�Z 
    float distancex = range_x + wihtd  / 2;
    float distancey = range_y + height / 2;
    //float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    // �������w�肳�ꂽ�͈͓��ł����true��Ԃ�  
    //Object��X���W���͈͂ɓ����Ă���Ȃ�
    if ((distancex + wihtd) * -1 <= circleposx && circleposx <= (distancex + wihtd))
    {
        //Object��Y���W���͈͂ɓ����Ă���Ȃ�
        if ((distancey + height) * -1 <= circleposy && circleposy <= (distancey + wihtd)){
            return true;
        }
        else{
            return false;
        }
    }
    else{ 
        return false;
    }

}

//�i������ 2024/11/25 ���]
// ��΂���
//�E����̒[����(�~�̐^�񒆂��O��)��������ɓ������Ă��鎞�ɔ��肪�������Ȃ�
//�E�΂߂ɂ����Ƃ��ɂ�����Ɖ~���H������(��Ԃ�΂����C���C������)
//���P��
//�E�p�̕��������ʂœ����蔻������
//�E�~�̐^�񒆂��������΂��Ă������Ă��炻���œ������Ă��锻��ɂ���


