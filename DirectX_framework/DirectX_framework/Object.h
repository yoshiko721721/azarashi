#pragma once
#include "camera.h"
#include "WICTextureLoader.h"

struct BoundingBox //�����蔻��Ŏg���ő�ŏ����W(�w�i�Ƃ��͎g��Ȃ��c�H�Ǝv�����̂ň�U�O�Ɂc)
{
	DirectX::XMFLOAT3 min; // �ŏ����W
	DirectX::XMFLOAT3 max; // �ő���W
};

class Object
{
private:
	Vertex vertexList[4] =
	{
		{ -0.5f,  0.5f, 0.5f, 1.0f, 1.1f, 1.0f, 1.0f, 0.0f, 0.0f },  // �O�Ԗڂ̒��_���W�@{ x, y, z }
		{  0.5f,  0.5f, 0.5f ,1.0f ,1.0f ,1.0f ,1.0f ,1.0f ,0.0f },  // �P�Ԗڂ̒��_���W
		{ -0.5f, -0.5f, 0.5f ,1.0f ,1.0f ,1.0f ,1.0f ,0.0f ,1.0f },  // �Q�Ԗڂ̒��_���W
		{  0.5f, -0.5f, 0.5f ,1.0f ,1.0f ,1.0f ,1.0f ,1.0f ,1.0f },
	};
	//���W
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	//�傫��
	DirectX::XMFLOAT3 size = { 100.0f,100.0f,0.0f };
	//�p�x
	float angle = 0.0f;

	DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f };

	//�e�N�X�`�����c���ɉ���������Ă��邩
	int splitX = 1;
	int splitY = 1;

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11ShaderResourceView* m_pTextureView;

public:
	float numU = 0;
	float numV = 0;

	virtual void Init()   = 0; //�h����
	virtual void Update() = 0;//�h���N���X�p
	void Uninit();
	void Initialize(const wchar_t* imgname, int sx = 1, int sy = 1); //������
	void Draw(Camera*);				//�`��

	//----------�Z�b�^�[�֌W--------------
	void SetPos(float x, float y, float z);
	void SetSize(float x, float y, float z);
	void SetAngle(float a);
	void SetColor(float r, float g, float b, float a);

	//----------�Q�b�^�[�֌W--------------
	DirectX::XMFLOAT3 GetPos(void);
	DirectX::XMFLOAT3 GetSize(void);
	float GetAngle(void);
	DirectX::XMFLOAT4 GetColor(void);

	//----------�����蔻��֌W---------------
	void UpdateBoundingBox();					//�ő�ŏ����W�����X�V����֐�
	void CheckCollision(/*const Object& other*/);	// �����蔻����`�F�b�N����֐�
};
