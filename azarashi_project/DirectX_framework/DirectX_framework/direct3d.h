#pragma once
#include <d3d11.h>  // DirectX11���g�����߂̃w�b�_�[�t�@�C��
#include <DirectXMath.h>

#define SCREEN_WIDTH (960)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (540)	// �E�C���h�E�̍���

// �֐��̃v���g�^�C�v�錾
HRESULT D3D_Create(HWND hwnd);	//
void    D3D_Release();			//
void    D3D_StartRender();		//
void    D3D_FinishRender();		//

struct Vertex//���_�f�[�^��\���\����
{
	float x, y, z;//�ꏊ

	float r, g, b, t;//�F

	float u, v;//�؂蔲��
};

struct ConstBuffer
{
	//���_�J���[�s��
	DirectX::XMFLOAT4 color;
	//UV���W�ړ��s��
	DirectX::XMMATRIX matrixTex;
	//�v���W�F�N�g�ϊ��s��
	DirectX::XMMATRIX matrixProj;
	//���[���h�ϊ��s��
	DirectX::XMMATRIX matrixWorld;
	//�r���[�ϊ��s��
	DirectX::XMMATRIX matrixView;
};

extern ID3D11Device* g_pDevice;
extern ID3D11DeviceContext* g_pDeviceContext;
extern ID3D11Buffer* g_pConstantBuffer;//�萔�o�b�t�@�𑼃t�@�C���Ƌ��L���邽�߂�extern��𗘗p���Ă�

//DirectX�̉���}�N��
#define SAFE_RELEASE(p){if(NULL != p){p->Release();p = NULL;}}
