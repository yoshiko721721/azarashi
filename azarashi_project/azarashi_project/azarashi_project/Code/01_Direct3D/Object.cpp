#include "object.h"
#include "../07_Camera/Camera.h"
#include"textureManager.h"

Object::Object(float posX, float posY, float sizeX, float sizeY)
{
	SetPos(posX, posY, 0);
	SetSize(sizeX, sizeY, 0);
}

void Object::Initialize(const wchar_t* imgname, int sx, int sy)
{
	splitX = sx;
	splitY = sy;
	vertexList[1].u = 1.0f / splitX;
	vertexList[2].v = 1.0f / splitY;
	vertexList[3].u = 1.0f / splitX;
	vertexList[3].v = 1.0f / splitY;

	//頂点バッファを作成する
	//※頂点バッファ→VRAMに頂点データを置くための機能
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);	//確保するバッファサイズを指定
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//頂点バッファ作成を指定
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;	//VRAMに送るデータを指定
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);

	//if (m_pTextureView == nullptr) // ★ テクスチャが読み込まれていない場合のみ読み込む
	//{
	//	テクスチャ読み込み
	//	hr = DirectX::CreateWICTextureFromFile(g_pDevice, imgname, NULL, &m_pTextureView);
	//	if (FAILED(hr))
	//	{
	//		MessageBoxA(NULL, "テクスチャ読み込み失敗", "エラー", MB_ICONERROR | MB_OK);
	//		return;
	//	}
	//}
	m_pTextureView = TextureManager::GetSRV(imgname);

}

void Object::Draw() {

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
	cb.matrixView = Camera::GetViewMatrix();
	cb.matrixView = DirectX::XMMatrixTranspose ( cb.matrixView );

	//ワールド変換行列の作成
	//→オブジェクトの位置・大きさ・向きを指定
	cb.matrixWorld = DirectX::XMMatrixScaling(size.x, size.y, size.z);
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(angle * 3.14f / 180);
	cb.matrixWorld *= DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

	//UVアニメーションの行列作成
	float u = (float)numU / splitX;
	float v = (float)numV / splitY;
	cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
	cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);
	cb.color = color;

	//行列をシェーダーに渡す
	g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

	g_pDeviceContext->Draw(5, 0);	//描画命令
}

void Object::Uninit() {
	//解放処理
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pTextureView);
}

void Object::SetPos(float x, float y, float z)
{
	//座標をセットする
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Object::SetSize(float x, float y, float z)
{
	//大きさをセットする
	size.x = x;
	size.y = y;
	size.z = z;
}

void Object::SetAngle(float a)
{
	//角度をセットする
	angle = a;
}

void Object::SetColor(float r, float g, float b, float a)
{
	//色をセットする
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}

DirectX::XMFLOAT3 Object::GetPos(void)
{
	return pos;	//座標をゲット
}

DirectX::XMFLOAT3 Object::GetSize(void)
{
	return size;	//大きさをゲット
}

float Object::GetAngle(void)
{
	return angle;	//角度をゲット
}

DirectX::XMFLOAT4 Object::GetColor(void)
{
	return color;	//色をゲット
}

void Object::SetTexture(const wchar_t* imgname)
{
	m_pTextureView->Release();
	m_pTextureView = nullptr;
	DirectX::CreateWICTextureFromFile(g_pDevice, imgname, NULL, &m_pTextureView);
}

void Object::SetTexture(ID3D11ShaderResourceView* mm_pTextureView)//Objectの色のセッター
{
	m_pTextureView = mm_pTextureView;
}