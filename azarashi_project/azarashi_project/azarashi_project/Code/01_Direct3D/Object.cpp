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

	//���_�o�b�t�@���쐬����
	//�����_�o�b�t�@��VRAM�ɒ��_�f�[�^��u�����߂̋@�\
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);	//�m�ۂ���o�b�t�@�T�C�Y���w��
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//���_�o�b�t�@�쐬���w��
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;	//VRAM�ɑ���f�[�^���w��
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);

	//if (m_pTextureView == nullptr) // �� �e�N�X�`�����ǂݍ��܂�Ă��Ȃ��ꍇ�̂ݓǂݍ���
	//{
	//	�e�N�X�`���ǂݍ���
	//	hr = DirectX::CreateWICTextureFromFile(g_pDevice, imgname, NULL, &m_pTextureView);
	//	if (FAILED(hr))
	//	{
	//		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
	//		return;
	//	}
	//}
	m_pTextureView = TextureManager::GetSRV(imgname);

}

void Object::Draw() {

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
	cb.matrixView = Camera::GetViewMatrix();
	cb.matrixView = DirectX::XMMatrixTranspose ( cb.matrixView );

	//���[���h�ϊ��s��̍쐬
	//���I�u�W�F�N�g�̈ʒu�E�傫���E�������w��
	cb.matrixWorld = DirectX::XMMatrixScaling(size.x, size.y, size.z);
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(angle * 3.14f / 180);
	cb.matrixWorld *= DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

	//UV�A�j���[�V�����̍s��쐬
	float u = (float)numU / splitX;
	float v = (float)numV / splitY;
	cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
	cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);
	cb.color = color;

	//�s����V�F�[�_�[�ɓn��
	g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

	g_pDeviceContext->Draw(5, 0);	//�`�施��
}

void Object::Uninit() {
	//�������
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pTextureView);
}

void Object::SetPos(float x, float y, float z)
{
	//���W���Z�b�g����
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Object::SetSize(float x, float y, float z)
{
	//�傫�����Z�b�g����
	size.x = x;
	size.y = y;
	size.z = z;
}

void Object::SetAngle(float a)
{
	//�p�x���Z�b�g����
	angle = a;
}

void Object::SetColor(float r, float g, float b, float a)
{
	//�F���Z�b�g����
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}

DirectX::XMFLOAT3 Object::GetPos(void)
{
	return pos;	//���W���Q�b�g
}

DirectX::XMFLOAT3 Object::GetSize(void)
{
	return size;	//�傫�����Q�b�g
}

float Object::GetAngle(void)
{
	return angle;	//�p�x���Q�b�g
}

DirectX::XMFLOAT4 Object::GetColor(void)
{
	return color;	//�F���Q�b�g
}

void Object::SetTexture(const wchar_t* imgname)
{
	m_pTextureView->Release();
	m_pTextureView = nullptr;
	DirectX::CreateWICTextureFromFile(g_pDevice, imgname, NULL, &m_pTextureView);
}

void Object::SetTexture(ID3D11ShaderResourceView* mm_pTextureView)//Object�̐F�̃Z�b�^�[
{
	m_pTextureView = mm_pTextureView;
}