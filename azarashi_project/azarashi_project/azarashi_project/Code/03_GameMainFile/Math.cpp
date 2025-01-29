#include "Math.h"

Radian Math::ConvertToRadian(Degree degree)
{
    return degree * (PI / 180);
}

Degree Math::ConvertToDegree(Radian radian)
{
    return radian * (180 / PI);
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
    Vector2 normal = 0;
    normal.x = point2.y - point1.y;
    normal.y = point1.x - point2.x;
    return normal.Normalize();
}

float Math::CalcSquareRoot(float x, float y)
{
    return sqrt(x * x + y * y);
}

Radian Math::NormalizeRadian(Radian radian)
{
    if (radian < 0)
        return radian + TAU;
    else if (radian >= TAU)
        return fmod(radian, TAU);
    else
        return radian;
}

Degree Math::NormalizeDegree(Degree degree)
{
    if (degree < 0)
        return degree + 360;
    else if (degree >= 360)
        return fmod(degree, 360);
    else
        return degree;
}
