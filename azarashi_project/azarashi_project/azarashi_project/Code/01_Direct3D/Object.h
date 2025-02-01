#pragma once
#include "direct3d.h"
#include "../05_WICTextureLoader/WICTextureLoader.h"

using DirectX::XMFLOAT3;
using DirectX::XMFLOAT4;

struct Circle
{
	float radius; // 半径
	float velocityX; // 垂直方向の速度
	float velocityY; // 垂直方向の速度
};

class Object {

private:
	//頂点データ
	Vertex vertexList[4] =
	{
		{ -0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{  0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
		{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
		{  0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	};

	//座標
	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	//大きさ
	DirectX::XMFLOAT3 size = { 100.0f, 100.0f, 0.0f };
	//角度
	float angle = 0.0f;
	//色
	DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	//テクスチャが縦横に何分割されているか
	int splitX = 1;
	int splitY = 1;

protected:
//頂点バッファ
	ID3D11Buffer* m_pVertexBuffer;
	//テクスチャ用変数
	ID3D11ShaderResourceView* m_pTextureView;

public:
	//右上から何話目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;

	Object() {}
	Object(float posX, float posY, float sizeX, float sizeY);

	void Initialize(const wchar_t* imgname, int sx = 1, int sy = 1);			//初期化
	virtual void Update() {};
	void Draw();										//描画
	void Uninit();										//終了
	void SetPos(float x, float y, float z);				//座標をセット
	void SetSize(float x, float y, float z);			//大きさをセット
	void SetAngle(float a);								//角度をセット
	void SetColor(float r, float g, float b, float a);	//色をセット
	void SetTexture(const wchar_t* imgname);
	void SetTexture(ID3D11ShaderResourceView* mm_pTextureView);//Objectの色のセッター

	XMFLOAT3 GetPos(void);		//座標をゲット
	XMFLOAT3 GetSize(void);		//大きさをゲット
	float GetAngle(void);				//角度をゲット
	XMFLOAT4 GetColor(void);	//色をゲット

	int GetSplitX(void)
	{
		return splitX;
	}

	int GetSplitY(void)
	{
		return splitY;
	}
};
