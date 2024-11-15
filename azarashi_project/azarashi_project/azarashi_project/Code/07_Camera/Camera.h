#pragma once
#include"../02_Input/input.h"
class Camera
{
public:
    Camera();
    ~Camera();
    void Init();
    void Update();
    void Draw();
    void Uninit();

    //セッター
    void SetPosition  (float x, float y, float z);               //cameraの位置をセットする
    void SetRotation  (DirectX::XMFLOAT3& rotation);             //cameraの回転をセットする
    void GetViewMatrix(DirectX::XMMATRIX viewMatrix);            //数値を取ってくる
    void GetProjectionMatrix(DirectX::XMMATRIX projectionMatrix);//数値を取ってくる

    //ゲッター
    DirectX::XMFLOAT3 GetPosition();
    DirectX::XMFLOAT3 GetRotation();
    DirectX::XMMATRIX GetViewMatrix();      //数値を取ってくる
    DirectX::XMMATRIX GetProjectionMatrix();//数値を取ってくる

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

protected:
    DirectX::XMFLOAT3 m_position = { 0.0f,0.0f,0.0f };//cameraの位置用の変数
    DirectX::XMFLOAT3 m_rotation;//cameraの回転率用の変数
    DirectX::XMMATRIX m_viewMatrix;//向きや回転率などを計算し、描画内容を決めたもの
    DirectX::XMMATRIX m_projectionMatrix;
};

