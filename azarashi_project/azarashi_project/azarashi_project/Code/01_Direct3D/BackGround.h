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
		//���_�o�b�t�@��ݒ�
		UINT strides = sizeof(Vertex);
		UINT offsets = 0;
		g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

		//�e�N�X�`�����s�b�N�Z���V�F�[�_�[�ɓn��
		g_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);

		//�萔�o�b�t�@���v�Z
		ConstBuffer cb;
		//�v���W�F�N�V�����ϊ��s����쐬
		cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, -300.0f, 300.0f);
		cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

		//�r���[�ϊ��s����쐬
		cb.matrixView = DirectX::XMMatrixIdentity();

		//���[���h�ϊ��s��̍쐬
		//���I�u�W�F�N�g�̈ʒu�E�傫���E�������w��
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

		//UV�A�j���[�V�����̍s��쐬
		float u = (float)numU / splitx;
		float v = (float)numV / splity;
		cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
		cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);
		cb.color = color;

		//�s����V�F�[�_�[�ɓn��
		g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

		g_pDeviceContext->Draw(5, 0);	//�`�施��

	}
};
