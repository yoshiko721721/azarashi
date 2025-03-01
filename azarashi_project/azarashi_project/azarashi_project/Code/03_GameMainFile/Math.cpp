#include "Math.h"

Radian Math::ConvertToRadian(Degree degree)
{
    return degree * (PI / 180.0f);
}

Degree Math::ConvertToDegree(Radian radian)
{
    return radian * (180.0f / PI);
}

//��̑��x���甽���W�� e ��Ԃ�
float Math::CoefficientOfRestitution(float v_Initial, float v_After) {
    float e = v_After / v_Initial;
    return abs(e);
}

// �ՓˑO�̑��x���v�Z����֐�
float Math::CalculateVelocityBeforeImpact(float setHeight, float gravity)
{
    //�K�����̒l(��Βl)�ɂ��ĕԂ�

    float temp = sqrt(2 * gravity * abs(setHeight));
    temp = abs(temp);
    return temp;
}

// �Փˌ�̑��x���擾����C���^�[�t�F�[�X
double Math::calculateRestitutionCoefficient(const std::function<float()>& velocityProvider)
{
    float velocityAfter = velocityProvider();
    return velocityAfter;
}

Vector2 Math::CalcNormal(const Vector2& point1, const Vector2& point2)
{
    Vector2 normal = 0.0f;
    normal.x = point2.y - point1.y;
    normal.y = point1.x - point2.x;
    return normal.Normalize();
}

float Math::CalcSquareRoot(float x, float y)
{
    if (x == 0.0f) { return y; }
    if (y == 0.0f) { return x; }
    else { return sqrt(x * x + y * y); }
}

float Math::dot(Vector2 v1, Vector2 v2)
{
    return v1.x * v2.x + v1.y * v2.y ;
}

Radian Math::NormalizeRadian(Radian radian)
{
    if (radian < 0.0f)
        return radian + TAU;
    else if (radian >= TAU)
        return fmod(radian, TAU);
    else
        return radian;
}

Degree Math::NormalizeDegree(Degree degree)
{
    if (degree < 0.0f)
        return degree + 360.0f;
    else if (degree >= 360.0f)
        return fmod(degree, 360.0f);
    else
        return degree;
}

//======================================
//          TransForm�������Ă���֐�
//======================================
TransForm TransForm::TransFormInitialize(Object& obj)
{
    //box�ɍ��W���i�[���Ă���
    TransForm box;

    box.position = { obj.GetPos().x      , obj.GetPos().y };			//���W
    box.halfSize = { obj.GetSize().x / 2 , obj.GetSize().y / 2 };		//�����̃T�C�Y
    box.angle = obj.GetAngle();								            //�p�x
    for (int i = 0; i < 4; ++i) {
        box.vertex[i] = GetObjectVertex(box, i);						//��]�ړ����l���������_
    }
    return box;
}

Vector2 TransForm::GetObjectVertex(TransForm transForm, int i)
{
    Vector2 vertex;
    Radian angle = Math::ConvertToRadian(transForm.angle);

    //�ꏊ�̐ݒ�
    switch (i)
    {
    case 0: vertex = { - transForm.halfSize.x,   transForm.halfSize.y };  break;	//����
    case 1: vertex = {   transForm.halfSize.x,   transForm.halfSize.y };  break;	//�E��
    case 2: vertex = {   transForm.halfSize.x, - transForm.halfSize.y };  break;	//�E��
    case 3: vertex = { - transForm.halfSize.x, - transForm.halfSize.y };  break;	//����
    default: return { -1.0f , -1.0f };
    }

    //��]�ړ�
    vertex.Rotate(angle);

    //���S���W�����Z
    vertex = { vertex.x + transForm.position.x , vertex.y + transForm.position.y };

    return vertex;
}
