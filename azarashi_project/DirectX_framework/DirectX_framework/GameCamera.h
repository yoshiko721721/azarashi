#pragma once
#include "camera.h"
#include "input.h"
using DirectX::XMFLOAT2;

class GameCamera :public Camera
{
public:
	void Init();
	void Update(float targetPosX,float targetPosY);
	void Draw();
	void Uninit();

	GameCamera();
	GameCamera(float, float);

	void SetPosition(float x, float y);				//座標セッター
	DirectX::XMMATRIX GetViewMatrix() const;		//ビュー行列ゲッター
	DirectX::XMMATRIX GetProjectionMatrix() const;	//射影行列ゲッター


private:
	Input input;
	DirectX::XMFLOAT3 position;				//カメラ座標
	DirectX::XMMATRIX viewMatrix;			//ビュー行列
	DirectX::XMMATRIX projectionMatrix;		//射影行列
	DirectX::XMFLOAT2 target;				//カメラの基準になるアザラシの座標を格納する変数

	void updateViewMatrix();				//ビュー行列更新
};