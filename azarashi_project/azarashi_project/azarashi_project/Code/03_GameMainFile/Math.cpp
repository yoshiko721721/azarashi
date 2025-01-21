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

//二つの速度から反発係数 e を返す
float Math::CoefficientOfRestitution(float v_Initial, float v_After) {
    float e = v_After / v_Initial;
    return ConvertAbsoluteValue(e);
}

// 衝突前の速度を計算する関数
float Math::CalculateVelocityBeforeImpact(float setHeight, float gravity)
{
    //必ず正の値(絶対値)にして返す

    float temp = sqrt(2 * gravity * ConvertAbsoluteValue(setHeight));
    temp = ConvertAbsoluteValue(temp);
    return temp;
}

// 衝突後の速度を取得するインターフェース
double Math::calculateRestitutionCoefficient(const std::function<float()>& velocityProvider)
{
    float velocityAfter = velocityProvider();
    return velocityAfter;
}

//絶対値にして返す
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