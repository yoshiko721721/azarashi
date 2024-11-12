#pragma once
#include "camera.h"
#include "WICTextureLoader.h"

struct BoundingBox //当たり判定で使う最大最小座標(背景とかは使わない…？と思ったので一旦外に…)
{
	DirectX::XMFLOAT3 min; // 最小座標
	DirectX::XMFLOAT3 max; // 最大座標
};

class Object
{
private:
	Vertex vertexList[4] =
	{
		{ -0.5f,  0.5f, 0.5f, 1.0f, 1.1f, 1.0f, 1.0f, 0.0f, 0.0f },  // ０番目の頂点座標　{ x, y, z }
		{  0.5f,  0.5f, 0.5f ,1.0f ,1.0f ,1.0f ,1.0f ,1.0f ,0.0f },  // １番目の頂点座標
		{ -0.5f, -0.5f, 0.5f ,1.0f ,1.0f ,1.0f ,1.0f ,0.0f ,1.0f },  // ２番目の頂点座標
		{  0.5f, -0.5f, 0.5f ,1.0f ,1.0f ,1.0f ,1.0f ,1.0f ,1.0f },
	};
	//座標
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	//大きさ
	DirectX::XMFLOAT3 size = { 100.0f,100.0f,0.0f };
	//角度
	float angle = 0.0f;

	DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f };

	//テクスチャが縦横に何分割されているか
	int splitX = 1;
	int splitY = 1;

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTextureView;

public:
	float numU = 0;
	float numV = 0;

	virtual void Init()   = 0; //派生側
	virtual void Update() = 0;//派生クラス用
	void Uninit();
	void Initialize(const wchar_t* imgname, int sx = 1, int sy = 1); //初期化
	void Draw(Camera*);				//描画

	//----------セッター関係--------------
	void SetPos(float x, float y, float z);
	void SetSize(float x, float y, float z);
	void SetAngle(float a);
	void SetColor(float r, float g, float b, float a);

	//----------ゲッター関係--------------
	DirectX::XMFLOAT3 GetPos(void);
	DirectX::XMFLOAT3 GetSize(void);
	float GetAngle(void);
	DirectX::XMFLOAT4 GetColor(void);

	//----------当たり判定関係---------------
	void UpdateBoundingBox();					//最大最小座標をを更新する関数
	void CheckCollision(/*const Object& other*/);	// 当たり判定をチェックする関数
};
