#include "Math.h"

#define PI 3.1415926535

float Math::ConvertDegreeToRadian()
{
    return PI / 180;
}

//二つの速度から反発係数 e を返す
float Math::CoefficientOfRestitution(float v_Initial,float v_After){
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
