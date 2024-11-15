#pragma once
#include "direct3d.h"
#include "../05_WICTextureLoader/WICTextureLoader.h"

using DirectX::XMFLOAT3;
using DirectX::XMFLOAT4;

class Object {

private:
	//���_�f�[�^
	Vertex vertexList[4] =
	{
		{ -0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
		{  0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
		{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
		{  0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	};

	//���_�o�b�t�@
	ID3D11Buffer* m_pVertexBuffer;
	//�e�N�X�`���p�ϐ�
	ID3D11ShaderResourceView* m_pTextureView;

	//���W
	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	//�傫��
	DirectX::XMFLOAT3 size = { 100.0f, 100.0f, 0.0f };
	//�p�x
	float angle = 0.0f;
	//�F
	DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	//�e�N�X�`�����c���ɉ���������Ă��邩
	int splitX = 1;
	int splitY = 1;

public:
	//�E�ォ�牽�b�ڂ�؂蔲���ĕ\�����邩
	float numU = 0;
	float numV = 0;

	void Init(const wchar_t* imgname, int sx = 1, int sy = 1);			//������
	void Draw();										//�`��
	void Uninit();										//�I��
	void SetPos(float x, float y, float z);				//���W���Z�b�g
	void SetSize(float x, float y, float z);			//�傫�����Z�b�g
	void SetAngle(float a);								//�p�x���Z�b�g
	void SetColor(float r, float g, float b, float a);	//�F���Z�b�g
	void SetTexture(const wchar_t* imgname);

	XMFLOAT3 GetPos(void);		//���W���Q�b�g
	XMFLOAT3 GetSize(void);		//�傫�����Q�b�g
	float GetAngle(void);				//�p�x���Q�b�g
	XMFLOAT4 GetColor(void);	//�F���Q�b�g
};