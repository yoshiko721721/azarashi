#pragma once
#include "Object.h"
#include "../02_Input/input.h"

class BackGround :public Object
{
private:

public:
	BackGround() {}
	~BackGround() { Uninit(); }

	void Draw()
	{
		//頂点バッファを設定
		UINT strides = sizeof(Vertex);
		UINT offsets = 0;
		g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

		//テクスチャをピックセルシェーダーに渡す
		g_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);

		//定数バッファを計算
		ConstBuffer cb;
		//プロジェクション変換行列を作成
		cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, -300.0f, 300.0f);
		cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

		//ビュー変換行列を作成
		cb.matrixView = DirectX::XMMatrixIdentity();

		//ワールド変換行列の作成
		//→オブジェクトの位置・大きさ・向きを指定
		DirectX::XMFLOAT3 size = GetSize();
		DirectX::XMFLOAT3 pos = GetPos();
		float angle = GetAngle();
		DirectX::XMFLOAT4 color = GetColor();
		cb.matrixWorld = DirectX::XMMatrixScaling(size.x, size.y, size.z);
		cb.matrixWorld *= DirectX::XMMatrixRotationZ(angle * 3.14f / 180);
		cb.matrixWorld *= DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
		cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

		int splitx = GetSplitX();
		int splity = GetSplitY();

		//UVアニメーションの行列作成
		float u = (float)numU / splitx;
		float v = (float)numV / splity;
		cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
		cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);
		cb.color = color;

		//行列をシェーダーに渡す
		g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

		g_pDeviceContext->Draw(5, 0);	//描画命令

	}
};
