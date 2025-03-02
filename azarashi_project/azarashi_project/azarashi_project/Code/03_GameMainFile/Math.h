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

struct TransForm {
	Vector2 position;
	Vector2 halfSize;
	float   angle;
	Vector2 vertex[4];

	/// @brief 中心座標、角度、ハーフサイズ 、実際の頂点座標を設定
	/// @param obj 上記4つに必要な情報を含むオブジェクト
	/// @return 角度も考慮されたboxにして返す
	TransForm TransFormInitialize(Object& obj);

	/// @brief 【forループ中に使う前提】４つの頂点を割り当てる
	/// @param box 中心座標、角度、ハーフサイズの情報を含んだ構造体
	/// @param i   ループカウンター変数
	/// @return 頂点を一つずつ返す
	Vector2   GetObjectVertex(TransForm transForm, int i);

};


namespace Math
{

	const float PI = 3.14159265f;
	const float TAU = 2.0f * PI;
	Radian ConvertToRadian(Degree degree);													//ラジアンの計算
	Degree ConvertToDegree(Radian radian);													//度数の計算
	float CoefficientOfRestitution(float v_Initial, float v_After);							//反発係数の計算
	float CalculateVelocityBeforeImpact(float setHeight, float gravity);					//衝突前の速度計算
	double calculateRestitutionCoefficient(const std::function<float()>& velocityProvider);	//衝突後の速度計算
	Vector2 CalcNormal(const Vector2& point1, const Vector2& point2);						//法線ベクトルを計算する
	float CalcAbs(float result);
	Degree CalcRefrectAngle(Degree myVec,Degree nrmVec);
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