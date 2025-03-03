#include "Math.h"

Radian Math::ConvertToRadian(Degree degree)
{
    return degree * (PI / 180.0f);
}

Degree Math::ConvertToDegree(Radian radian)
{
    return radian * (180.0f / PI);
}

//二つの速度から反発係数 e を返す
float Math::CoefficientOfRestitution(float v_Initial, float v_After) {
    float e = v_After / v_Initial;
    return abs(e);
}

// 衝突前の速度を計算する関数
float Math::CalculateVelocityBeforeImpact(float setHeight, float gravity)
{
    //必ず正の値(絶対値)にして返す

    float temp = sqrt(2 * gravity * abs(setHeight));
    temp = abs(temp);
    return temp;
}

// 衝突後の速度を取得するインターフェース
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

float Math::CalcAbs(float result)
{
    if (result < 0) {
        result *= - 1;
    }
    return result;
}

Degree Math::CalcRefrectAngle(Degree myAngle, Degree nrmAngle)
{
    myAngle = Math::NormalizeDegree(myAngle);
    Degree angle = fmod(myAngle, 180);
    Degree result = 2 * nrmAngle - angle;

    return result;
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
//          TransFormが持っている関数
//======================================
TransForm TransForm::TransFormInitialize(Object& obj)
{
    //boxに座標を格納していく
    TransForm box;

    box.position = { obj.GetPos().x      , obj.GetPos().y };			//座標
    box.halfSize = { obj.GetSize().x / 2 , obj.GetSize().y / 2 };		//半分のサイズ
    box.angle = obj.GetAngle();								            //角度
    for (int i = 0; i < 4; ++i) {
        box.vertex[i] = GetObjectVertex(box, i);						//回転移動も考慮した頂点
    }
    return box;
}

Vector2 TransForm::GetObjectVertex(TransForm transForm, int i)
{
    Vector2 vertex;
    Radian angle = Math::ConvertToRadian(transForm.angle);

    //場所の設定
    switch (i)
    {
    case 0: vertex = { - transForm.halfSize.x, - transForm.halfSize.y };  break;	//左下
    case 1: vertex = {   transForm.halfSize.x, - transForm.halfSize.y };  break;	//右下
    case 2: vertex = {   transForm.halfSize.x,   transForm.halfSize.y };  break;	//右上
    case 3: vertex = { - transForm.halfSize.x,   transForm.halfSize.y };  break;	//左上
    default: return { -1.0f , -1.0f };
    }

    //回転移動
    vertex = vertex.Rotate(angle);

    //中心座標を加算
    vertex = { vertex.x + transForm.position.x , vertex.y + transForm.position.y };

    return vertex;
}
