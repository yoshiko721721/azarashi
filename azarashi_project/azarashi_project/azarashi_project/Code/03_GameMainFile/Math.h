#pragma once
#include <DirectXMath.h>
#include <functional>

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


	//長さを取得
	float Length() const { return sqrt(x * x + y * y); }

	//正規化
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


namespace Math
{

	const float PI = 3.1416f;
	const float TAU = 2 * PI;
	Radian ConvertToRadian(Degree degree);													//ラジアンの計算
	Degree ConvertToDegree(Radian radian);													//度数の計算
	float CoefficientOfRestitution(float v_Initial, float v_After);							//反発係数の計算
	float CalculateVelocityBeforeImpact(float setHeight, float gravity);					//衝突前の速度計算
	double calculateRestitutionCoefficient(const std::function<float()>& velocityProvider);	//衝突後の速度計算
	Vector2 CalcNormal(const Vector2& point1, const Vector2& point2);						//法線ベクトルを計算する
	float CalcSquareRoot(float x, float y);
	float dot(Vector2 v1,Vector2 v2);

	//float Vector2Point(const Vector2 v1, const Vector2 v2) { return static_cast<float>(v1.x * v2.x + v1.y * v2.y) ; }	//接線ベクトル
	//Vector2 Vector2Lerp (const Vector2 v1, const Vector2 v2, float t)  { return v1 + (v2 - v1) * t; }

	/// @brief 角度を正規化
	/// @param radian 角度
	/// @return 0~2π
	Radian NormalizeRadian(Radian radian);

	/// @brief 角度（Degree）を正規化
	/// @param degree 角度
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