#include "Math.h"


float Math::MaintenanceRadian(float radian)
{
    if (radian < 0) {

        radian += Math::tau;
    }
    else if (radian > Math::tau) {

        radian = fmod(radian, Math::tau);
    }

    return radian;
}

float Math::ConvertDegreeToRadian()
{
    return PI / 180;
}

float Math::ConvertDegreeToMethod()
{
    return 180 / PI;
}

//��̑��x���甽���W�� e ��Ԃ�
float Math::CoefficientOfRestitution(float v_Initial, float v_After) {
    float e = v_After / v_Initial;
    return ConvertAbsoluteValue(e);
}

// �ՓˑO�̑��x���v�Z����֐�
float Math::CalculateVelocityBeforeImpact(float setHeight, float gravity)
{
    //�K�����̒l(��Βl)�ɂ��ĕԂ�

    float temp = sqrt(2 * gravity * ConvertAbsoluteValue(setHeight));
    temp = ConvertAbsoluteValue(temp);
    return temp;
}

// �Փˌ�̑��x���擾����C���^�[�t�F�[�X
double Math::calculateRestitutionCoefficient(const std::function<float()>& velocityProvider)
{
    float velocityAfter = velocityProvider();
    return velocityAfter;
}

//��Βl�ɂ��ĕԂ�
float Math::ConvertAbsoluteValue(float AbsValue)
{
    AbsValue = (AbsValue >= 0) ? AbsValue : -AbsValue;
    return AbsValue;
}


float Math::VectorLength(const Vector2& vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float Math::CalcSquareRoot(float x, float y)
{
    return sqrt(x * x + y * y);
}

Vector2 Math::Normalize(const Vector2& vector)
{
    float length = VectorLength(vector);
    if (length == 0) {
        return { 0,0 };
    }
    return { vector.x / length , vector.y / length };
}

Vector2 Math::CalculateNormal(const Vector2& point1, const Vector2& point2)
{
    Vector2 normal;
    normal.x = point2.y - point1.y;
    normal.y = point1.x - point2.x;
    return Normalize(normal);
}