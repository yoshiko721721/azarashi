#pragma once
#include <DirectXMath.h>
#include <functional>

#define FRAMERATE 60 

class Vector2 {
public:
	float x, y;
	Vector2(float x = 0.0, float y = 0.0) : x(x), y(y) {};

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator/(const Vector2& other) const
	{
		return Vector2(x / other.x, y / other.y);
	}

	Vector2 operator=(const Vector2& other) const
	{
		return Vector2(other.x, other.y);
	}

	Vector2 operator+=(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator*(float scalar) const {
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator*=(float scalar) const {
		return Vector2(x * scalar, y * scalar);
	}
};


namespace Math
{
	float ConvertDegreeToRadian();													//ラジアンの計算
	float CoefficientOfRestitution(float v_Initial, float v_After);								//反発係数の計算
	float CalculateVelocityBeforeImpact(float setHeight,float gravity);							//衝突前の速度計算
	double calculateRestitutionCoefficient(const std::function<float ()>& velocityProvider);	//衝突後の速度計算
	float ConvertAbsoluteValue(float AbsValue);													//絶対値
};
