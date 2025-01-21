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

	bool operator>(float scalar) const {
		if (x > scalar && y > scalar) {
			return true;
		}
		return false;
	}
	bool operator>=(float scalar) const {
		if (x >= scalar && y >= scalar) {
			return true;
		}
		return false;
	}
	bool operator<(float scalar) const {
		if (x < scalar && y < scalar) {
			return true;
		}
		return false;
	}
	bool operator<=(float scalar) const {
		if (x <= scalar && y <= scalar) {
			return true;
		}
		return false;
	}

};


namespace Math
{

	const float PI = 3.1415926535;
	const float tau = 2 * Math::PI;
	float MaintenanceRadian(float);																//���W�A����0 =< x < tau�ɂ��邽�߂̊֐�
	float ConvertDegreeToRadian();																//���W�A���̌v�Z
	float ConvertDegreeToMethod();																//�x���̌v�Z
	float CoefficientOfRestitution(float v_Initial, float v_After);								//�����W���̌v�Z
	float CalculateVelocityBeforeImpact(float setHeight, float gravity);							//�ՓˑO�̑��x�v�Z
	double calculateRestitutionCoefficient(const std::function<float()>& velocityProvider);	//�Փˌ�̑��x�v�Z
	float ConvertAbsoluteValue(float AbsValue);													//��Βl
	float VectorLength(const Vector2& vector);													//�x�N�g���̒������v�Z
	float CalcSquareRoot(float x, float y);													//�����������߂�
	Vector2 Normalize(const Vector2& vector);													//�x�N�g���𐳋K��
	Vector2 CalculateNormal(const Vector2& point1, const Vector2& point2);						//�@���x�N�g�����v�Z����
};