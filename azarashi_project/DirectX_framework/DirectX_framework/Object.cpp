#include "Object.h"
void Object::Initialize(const wchar_t* imgname, int sx, int sy)
{
	splitX = sx;
	splitY = sy;
	vertexList[1].u = 1.0f / splitX;
	vertexList[2].v = 1.0f / splitY;
	vertexList[3].u = 1.0f / splitX;
	vertexList[3].v = 1.0f / splitY;

	//���_�o�b�t�@�𐧍삷��
	//�����_�o�b�t�@��VRAM�ɒ��_�f�[�^��u�����߂̋@�\
	D3D11_BUFFER_DESC bufferDesc;///�T�C�g����vbDesc
	bufferDesc.ByteWidth = sizeof(vertexList);//�m�ۂ���o�b�t�@�T�C�Y���w��
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//���_�o�b�t�@������w��

	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// VRAM�ɑ���f�[�^���w��
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);

	//�e�N�X�`���ǂݍ���
	hr = DirectX::CreateWICTextureFromFile(g_pDevice, imgname, NULL, &m_pTextureView);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);

		return;
	}
}

void Object::Draw(Camera* Camera)//�J�����𓮂������߂ɃJ�����̃|�C���^�������Ă���������
{
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);
	g_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);

	//�萔�o�b�t�@���X�V
	ConstBuffer cb;
	//�v���W�F�N�V�����ϊ��s��
	cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
	cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);
	/*Camera->UpdateProjectionMatrix();
	cb.matrixProj = Camera->GetProjectionMatrix();*/

	//�r���[�ϊ��s��
	/*Camera->UpdateViewMatrix();
	cb.matrixView = Camera->GetViewMatrix();*/

	//���[���h�ϊ��s��̐���
	// ���I�u�W�F�N�g�̈ʒu�E�傫���E�������w��
	cb.matrixWorld = DirectX::XMMatrixScaling(size.x, size.y, size.z);
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(angle * 3.14f / 180);
	cb.matrixWorld *= DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

	//UV�A�j���[�V�����̍s��쐬
	float u = (float)numU / splitX;
	float v = (float)numV / splitY;
	cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
	cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

	// �r���[�s����v�Z
	DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet(0.5f, 0.5f, 0.0f, 1.0f);
	DirectX::XMVECTOR focusPoint  = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR upDirection = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//ViewMatrix��cb��ViewMatrix�ɓ���Ȃ��Ƃ����Ȃ���
	//ProjectionMatrix�����l�ɓ���Ȃ��Ƃ����Ȃ���
	
	//cb.matrixView = DirectX::XMMatrixLookAtLH(eyePosition, focusPoint, upDirection);

	//���_�J���[�̃f�[�^����
	cb.color = color;

	//�s��V�F�[�_�[�ɓn��
	g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);


	g_pDeviceContext->Draw(4, 0); // �`�施��

}

void Object::Uninit()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pTextureView);
}

void Object::SetPos(float x, float y, float z)//Object��position�̃Z�b�^�[
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Object::SetSize(float x, float y, float z)//Object��size�̃Z�b�^�[
{
	size.x = x;
	size.y = y;
	size.z = z;
}

void Object::SetAngle(float a)//Object�̊p�x�̃Z�b�^�[
{
	angle = a;
}

void Object::SetColor(float r, float g, float b, float a)//Object�̐F�̃Z�b�^�[
{
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}

DirectX::XMFLOAT3 Object::GetPos(void)//position�̃Q�b�^�[
{
	return pos;
}

DirectX::XMFLOAT3 Object::GetSize(void)//size�̃Q�b�^�[
{
	return size;
}

float Object::GetAngle(void)//�p�x�̃Z�b�^�[
{
	return angle;
}

DirectX::XMFLOAT4 Object::GetColor(void)
{
	return color;
}

void Object::CheckCollision()
{


}

void Object::UpdateBoundingBox()
{


}