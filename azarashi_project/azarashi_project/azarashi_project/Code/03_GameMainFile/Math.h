#pragma once
#include <DirectXMath.h>
#include <functional>
#include "../01_Direct3D/Object.h"

#define FRAMERATE 60 

using namespace std;
using namespace DirectX;

typedef float Degree;
typedef float Radian;

struct Vector2 {
	float x, y;
	Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {};
	Vector2(XMFLOAT3 f3) : x(f3.x), y(f3.y) {};

	Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
	Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
	Vector2 operator/(const float scalar) const { return Vector2(x / scalar, y / scalar); }
	Vector2 operator*(const float scalar) const { return Vector2(x * scalar, y * scalar); }

	Vector2& operator+=(const Vector2& v) noexcept { x += v.x; y += v.y; return *this; }
	Vector2& operator-=(const Vector2& v) noexcept { x -= v.x; y -= v.y; return *this; }

	operator XMFLOAT2() { return XMFLOAT2{ x, y }; }


	//�������擾
	float Length() const { return sqrt(x * x + y * y); }

	//���K��
	Vector2 Normalize() const noexcept
	{
		float length = Length();
		if (length != 0)
			return Vector2{ x / length, y / length };
	}

	Vector2 Rotate(const Radian angle) const noexcept
	{
		float sinA = sin(angle);
		float cosA = cos(angle);
		return { x * cosA - y * sinA, x * sinA + y * cosA };
	}

	

};

struct TransForm {
	Vector2 position;
	Vector2 halfSize;
	float   angle;
	Vector2 vertex[4];

	/// @brief ���S���W�A�p�x�A�n�[�t�T�C�Y �A���ۂ̒��_���W��ݒ�
	/// @param obj ��L4�ɕK�v�ȏ����܂ރI�u�W�F�N�g
	/// @return �p�x���l�����ꂽbox�ɂ��ĕԂ�
	TransForm TransFormInitialize(Object& obj);

	/// @brief �yfor���[�v���Ɏg���O��z�S�̒��_�����蓖�Ă�
	/// @param box ���S���W�A�p�x�A�n�[�t�T�C�Y�̏����܂񂾍\����
	/// @param i   ���[�v�J�E���^�[�ϐ�
	/// @return ���_������Ԃ�
	Vector2   GetObjectVertex(TransForm transForm, int i);

};


namespace Math
{

	const float PI = 3.14159265f;
	const float TAU = 2.0f * PI;
	Radian ConvertToRadian(Degree degree);													//���W�A���̌v�Z
	Degree ConvertToDegree(Radian radian);													//�x���̌v�Z
	float CoefficientOfRestitution(float v_Initial, float v_After);							//�����W���̌v�Z
	float CalculateVelocityBeforeImpact(float setHeight, float gravity);					//�ՓˑO�̑��x�v�Z
	double calculateRestitutionCoefficient(const std::function<float()>& velocityProvider);	//�Փˌ�̑��x�v�Z
	Vector2 CalcNormal(const Vector2& point1, const Vector2& point2);						//�@���x�N�g�����v�Z����
	float CalcAbs(float result);
	Degree CalcRefrectAngle(Degree myVec,Degree nrmVec);
	float CalcSquareRoot(float x, float y);
	float dot(Vector2 v1,Vector2 v2);

	//float Vector2Point(const Vector2 v1, const Vector2 v2) { return static_cast<float>(v1.x * v2.x + v1.y * v2.y) ; }	//�ڐ��x�N�g��
	//Vector2 Vector2Lerp (const Vector2 v1, const Vector2 v2, float t)  { return v1 + (v2 - v1) * t; }

	/// @brief �p�x�𐳋K��
	/// @param radian �p�x
	/// @return 0~2��
	Radian NormalizeRadian(Radian radian);

	/// @brief �p�x�iDegree�j�𐳋K��
	/// @param degree �p�x
	/// @return 0~360
	Degree NormalizeDegree(Degree degree);
};

template <typename T>
constexpr const T& clamp(const T& value, const T& min, const T& max) {
	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}
	else {
		return value;
	}
}