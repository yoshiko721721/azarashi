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
	float ConvertDegreeToRadian();													//���W�A���̌v�Z
	float CoefficientOfRestitution(float v_Initial, float v_After);								//�����W���̌v�Z
	float CalculateVelocityBeforeImpact(float setHeight,float gravity);							//�ՓˑO�̑��x�v�Z
	double calculateRestitutionCoefficient(const std::function<float ()>& velocityProvider);	//�Փˌ�̑��x�v�Z
	float ConvertAbsoluteValue(float AbsValue);													//��Βl
};
