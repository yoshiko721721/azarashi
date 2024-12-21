#include "CircleCollider.h"
#include <algorithm>

// �X�R�[�v��t����hitcorners ���` 
DirectX::XMFLOAT2 CircleCollider::hitcorners[4];

//--------------------------------------------------------------
//�X���ɍ��킹�Ē����`�̊p�x�v�Z�֐�(��]���W)
// //2024/11/14 ���]
//--------------------------------------------------------------
DirectX::XMFLOAT2 CircleCollider::RotatePosition(/*��`�̒��S���W*/DirectX::XMFLOAT2 point, /*��`�̊p�x*/float angle)
{
    DirectX::XMFLOAT2 result;
    result.x = point.x * cos(angle) - point.y * sin(angle);//��]�s����g����X���W��ύX�����
    result.y = point.x * sin(angle) + point.y * cos(angle);//��]�s����g����Y���W��ύX����� 
    return result;
}

// �x�N�g���̓��ς��v�Z 
float CircleCollider::dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

//--------------------------------------------------------------
//�l�p�Ɖ~�̓����蔻��֐�
//2024/11/14 ���]
//--------------------------------------------------------------
ContactPointVector CircleCollider::ColliderWithBox(Object* p_Box, Object* p_Circle)
{
    float angle = p_Box->GetAngle();     //�l�p�̊p�x���擾
    angle = angle * (M_PI / 180.0);      //�l�p�̊p�x�����W�A���ɕϊ�

    DirectX::XMFLOAT3 boxpos = p_Box->GetPos();   //�|�C���^�[���g����circle�̍��W�擾
    //DirectX::XMFLOAT3 boxpos2 = { boxpos.x,boxpos.y };
    DirectX::XMFLOAT3 boxsize = p_Box->GetSize();  //�|�C���^�[���g����circle�̃T�C�Y�擾

    DirectX::XMFLOAT3 circlepos = p_Circle->GetPos();   //�|�C���^�[���g����circle�̍��W�擾
    DirectX::XMFLOAT3 circlesize = p_Circle->GetSize();  //�|�C���^�[���g����circle�̃T�C�Y�擾

    //��`�̕��ƍ����𔼕��ɂ��Ă������Ƃō��W�v�Z���ȒP�ɂȂ�
    DirectX::XMFLOAT2 halfsize = { boxsize.x / 2 , boxsize.y / 2 };//OK

    //���̔����ƍ����̔����̐��l���g���Ē����`�̒��_�̍��W���v�Z����(o^�\^o)
    hitcorners[0] = { -halfsize.x , -halfsize.y };
    hitcorners[1] = {  halfsize.x , -halfsize.y };
    hitcorners[2] = {  halfsize.x ,  halfsize.y };
    hitcorners[3] = { -halfsize.x ,  halfsize.y };//OK

    //��]��A���s�ړ���̍��W�ɕϊ�(�l�p���ׂ�)
    for (int i = 0; i < 4; i++) {
        hitcorners[i] = RotatePosition(hitcorners[i], angle);//�����`�̊e�p����]������
        hitcorners[i].x += boxpos.x;//�ϊ�������`��X�ɋ�`�̒��S���WX�𑫂�
        hitcorners[i].y += boxpos.y;//�ϊ�������`��Y�ɋ�`�̒��S���WY�𑫂�

    }//OK

     // �e�ӂƉ~�Ƃ̋����𔻒�
    for (int i = 0; i < 4; i++)
    {
        DirectX::XMFLOAT2 p1 = hitcorners[i];
        DirectX::XMFLOAT2 p2 = hitcorners[(i + 1) % 4];

        // �ӂ̕����x�N�g��
        DirectX::XMFLOAT2 edge = { p2.x - p1.x, p2.y - p1.y };//�p����p�̃x�N�g����}���
        DirectX::XMFLOAT2 toCircle = { circlepos.x - p1.x, circlepos.y - p1.y };//�_����p�̃x�N�g����}���

        float t = fmax(0, fmin(1, (toCircle.x * edge.x + toCircle.y * edge.y) / (edge.x * edge.x + edge.y * edge.y)));
        DirectX::XMFLOAT2 closestPoint = { p1.x + t * edge.x, p1.y + t * edge.y }; //�Ԃ��l

        // �ŋߐړ_�Ɖ~�̒��S�̋������v�Z
        float distanceSquared = (closestPoint.x - circlepos.x) * (closestPoint.x - circlepos.x) + (closestPoint.y - circlepos.y) * (closestPoint.y - circlepos.y);//�Ԃ��l

        // ���������a�ȉ��Ȃ瓖����Ɣ���
        if (distanceSquared <= (circlesize.y / 2) * (circlesize.y / 2))
        {
            DirectX::XMFLOAT2 vectorToCenter = { closestPoint.x - circlepos.x , closestPoint.y - circlepos.y };
            float length = sqrt(vectorToCenter.x * vectorToCenter.x + vectorToCenter.y * vectorToCenter.y);
            DirectX::XMFLOAT2 normalizedVector = { vectorToCenter.x / length, vectorToCenter.y / length };
            //closscircle = closestPoint;
            //distancesquared = distanceSquared;

            return { true, closestPoint ,normalizedVector };
        }
    }

    return { false };
};
//--------------------------------------------------------------
//�l�p�Ǝl�p�̓����蔻��֐�
//2024/12/03 ���]
//--------------------------------------------------------------
bool CircleCollider::ColliderWithCircle(Object* p_Circle1, Object* p_Circle2)
{
    DirectX::XMFLOAT3 circlepos1 = p_Circle1->GetPos();
    DirectX::XMFLOAT3 circlesize1 = p_Circle1->GetSize();  //�|�C���^�[���g����circle�̃T�C�Y�擾

    DirectX::XMFLOAT3 circlepos2 = p_Circle2->GetPos();
    DirectX::XMFLOAT3 circlesize2 = p_Circle2->GetSize();  //�|�C���^�[���g����circle�̃T�C�Y�擾

    float radius1 = circlesize1.y / 2;
    float radius2 = circlesize2.y / 2;

    float a = circlepos1.x - circlepos2.x;
    float b = circlepos1.y - circlepos2.y;
    float c = sqrt(a * a + b * b);

    if (c <= radius1 + radius2)
    {
        return true;
    }
    else
    { 
        return false;
    }
}
//--------------------------------------------------------------
//�͈͓���circle���Ȃɂ����邩�ǂ����𒲂ׂ�֐�
//2024/11/23 ���]
//--------------------------------------------------------------
/* bool CircleCollider::IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height)
{
   // ��`�̒��S����~�̒��S�܂ł̋������v�Z 
    float distancex = range_x + wihtd / 2;
    float distancey = range_y + height / 2;
    //float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    // �������w�肳�ꂽ�͈͓��ł����true��Ԃ�  
    DirectX::XMFLOAT3 circlesize = { 50,50,0 };
    //Object��X���W���͈͂ɓ����Ă���Ȃ�
    if ((distancex + wihtd) * -1 <= circleposx && circleposx <= (distancex + wihtd)) {
        //Object��Y���W���͈͂ɓ����Ă���Ȃ�
        if ((distancey + height) * -1 <= circleposy && circleposy <= (distancey + wihtd)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

}*/


