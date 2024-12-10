#include "BoxCollider.h"
#include "../03_GameMainFile/Math.h"

using namespace Math;


//--------------------------------------------------------------
//�X���ɍ��킹�Ē����`�̊p�x�v�Z�֐�(��]���W)
// //2024/11/14 ���]
//--------------------------------------------------------------
DirectX::XMFLOAT2 BoxCollider::RotatePosition(/*��`�̒��S���W*/DirectX::XMFLOAT2 point, /*��`�̊p�x*/float angle)
{
    DirectX::XMFLOAT2 result;
    result.x = point.x * cos(angle) - point.y * sin(angle);  //��]�s����g����X���W��ύX�����
    result.y = point.x * sin(angle) + point.y * cos(angle);  //��]�s����g����Y���W��ύX����� 
    return result;
}

//--------------------------------------------------------------
//�l�p�Ɖ~�̓����蔻��֐�
//2024/11/14 ���]
//--------------------------------------------------------------
bool BoxCollider::CheckCollision_Box_Circle(Object* m_GamePlayer,Object* p_block)
{
    const float angle = p_block->GetAngle() * ConvertDegreeToRadian();   //�p�x�����W�A���ɕϊ�

    DirectX::XMFLOAT3 circlepos = m_GamePlayer->GetPos();   //�|�C���^�[���g����circle�̍��W�擾
    DirectX::XMFLOAT3 circlesize =m_GamePlayer->GetSize();  //�|�C���^�[���g����circle�̃T�C�Y�擾

    //��`�̕��ƍ����𔼕��ɂ��Ă������Ƃō��W�v�Z���ȒP�ɂȂ�
    DirectX::XMFLOAT2 halfsize = { p_block->GetSize().x / 2, p_block->GetSize().y / 2 };

    //���̔����ƍ����̔����̐��l���g���Ē����`�̒��_�̍��W���v�Z����(o^�\^o)
    hitcorners[0] = { -halfsize.x , -halfsize.y };      //����
    hitcorners[1] = {  halfsize.x , -halfsize.y };      //�E��
    hitcorners[2] = {  halfsize.x ,  halfsize.y };      //�E��
    hitcorners[3] = { -halfsize.x ,  halfsize.y };      //����

    //��]��A���s�ړ���̍��W�ɕϊ�(�l�p���ׂ�)
    for (int i = 0; i < 4; i++) {
        hitcorners[i] = RotatePosition(hitcorners[i], angle);//�����`�̊e�p����]������
        hitcorners[i].x += p_block->GetPos().x ;//�ϊ�������`��X�ɋ�`�̒��S���WX�𑫂�
        hitcorners[i].y += p_block->GetPos().y ;//�ϊ�������`��Y�ɋ�`�̒��S���WY�𑫂�
       
    }

     // �e�ӂƉ~�Ƃ̋����𔻒�
    for (int i = 0; i < 4; i++)
    {
        DirectX::XMFLOAT2 p1 = hitcorners[i];
        DirectX::XMFLOAT2 p2 = hitcorners[(i + 1) % 4];

        // �ӂ̕����x�N�g��
        DirectX::XMFLOAT2 edge = { p2.x - p1.x, p2.y - p1.y };                  //�p����p�̃x�N�g����}���
        DirectX::XMFLOAT2 toCircle = { circlepos.x - p1.x, circlepos.y - p1.y };//�_����p�̃x�N�g����}���

        float t = fmaxf(0 , fminf(1, (toCircle.x * edge.x + toCircle.y * edge.y) / (edge.x * edge.x + edge.y * edge.y)));
        DirectX::XMFLOAT2 closestPoint = { p1.x + t * edge.x, p1.y + t * edge.y };

        // �ŋߐړ_�Ɖ~�̒��S�̋������v�Z
        float distanceSquared = (closestPoint.x - circlepos.x) * (closestPoint.x - circlepos.x) +
                                (closestPoint.y - circlepos.y) * (closestPoint.y - circlepos.y);
        // ���������a�ȉ��Ȃ瓖����Ɣ���
        if (distanceSquared <= circlesize.y / 2 * circlesize.y / 2)
        {
          return true;
        }
    }

    return false;
};

//--------------------------------------------------------------
//�l�p�Ǝl�p�̓����蔻��֐�
//2024/12/03 ���]
//--------------------------------------------------------------
bool BoxCollider::CheckCollision_Box_Box(Object* m_GamePlayer, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height)
{
    return false;
}

//--------------------------------------------------------------
//�Փ˔�������͈͂ɂ��̃I�u�W�F�N�g���邩�ǂ����𒲂ׂ�֐�
//2024/12/7 ���] (���������������������̂ł܂����ǔł��ڂ���)
//--------------------------------------------------------------
bool BoxCollider::IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height)
{
    // ��`�̒��S����~�̒��S�܂ł̋������v�Z 
    float distancex = range_x + wihtd / 2;
    float distancey = range_y + height / 2;
    //float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    // �������w�肳�ꂽ�͈͓��ł����true��Ԃ�  
    DirectX::XMFLOAT3 circlesize = { 50,50,0 };
    //Object��X���W���͈͂ɓ����Ă���Ȃ�
    if ((distancex + wihtd) * -1 <= circleposx && circleposx <= (distancex + wihtd)){
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


