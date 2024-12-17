#include "Renderer.h"
#include "Application.h"

using namespace DirectX::SimpleMath;

// D3D_FEATURE_LEVEL��Direct3D�̃o�[�W����
D3D_FEATURE_LEVEL Renderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device* Renderer::m_Device{}; // Direct3D�f�o�C�X
ID3D11DeviceContext* Renderer::m_DeviceContext{}; // �f�o�C�X�R���e�L�X�g
IDXGISwapChain* Renderer::m_SwapChain{}; // �X���b�v�`�F�[��
ID3D11RenderTargetView* Renderer::m_RenderTargetView{}; // �����_�[�^�[�Q�b�g�r���[
ID3D11DepthStencilView* Renderer::m_DepthStencilView{}; // �f�v�X�X�e���V���r���[

ID3D11Buffer* Renderer::m_WorldBuffer{}; // ���[���h�s��
ID3D11Buffer* Renderer::m_ViewBuffer{}; // �r���[�s��
ID3D11Buffer* Renderer::m_ProjectionBuffer{}; // �v���W�F�N�V�����s��

// �f�v�X�X�e���V���X�e�[�g
ID3D11DepthStencilState* Renderer::m_DepthStateEnable{};
ID3D11DepthStencilState* Renderer::m_DepthStateDisable{};

ID3D11BlendState* Renderer::m_BlendState[MAX_BLENDSTATE]; // �u�����h�X�e�[�g�z��
ID3D11BlendState* Renderer::m_BlendStateATC{}; // ����̃A���t�@�e�X�g�ƃJ�o���b�W�iATC�j�p�̃u�����h�X�e�[�g


//=======================================
//����������
//=======================================
void Renderer::Init()
{
	HRESULT hr = S_OK;

	// �f�o�C�X�A�X���b�v�`�F�[���쐬
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1; // �o�b�N�o�b�t�@�̐���1�ɐݒ�i�_�u���o�b�t�@�����O�j
	swapChainDesc.BufferDesc.Width = Application::GetWidth(); // �o�b�t�@�̕����E�B���h�E�T�C�Y�ɍ��킹��
	swapChainDesc.BufferDesc.Height = Application::GetHeight(); // �o�b�t�@�̍������E�B���h�E�T�C�Y�ɍ��킹��
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �o�b�t�@�̃s�N�Z���t�H�[�}�b�g��ݒ�
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // ���t���b�V�����[�g��ݒ�iHz�j
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // �o�b�t�@�̎g�p�p�r��ݒ�
	swapChainDesc.OutputWindow = Application::GetWindow(); // �X���b�v�`�F�[���̃^�[�Q�b�g�E�B���h�E��ݒ�
	swapChainDesc.SampleDesc.Count = 1; // �}���`�T���v�����O�̐ݒ�i�A���`�G�C���A�X�̃T���v�����ƃN�I���e�B�j
	swapChainDesc.SampleDesc.Quality = 0; //����
	swapChainDesc.Windowed = TRUE; // �E�B���h�E���[�h�i�t���X�N���[���ł͂Ȃ��A�E�B���h�E���[�h�Ŏ��s�j

	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, 
		D3D11_SDK_VERSION, &swapChainDesc, &m_SwapChain, &m_Device, &m_FeatureLevel, &m_DeviceContext);
	if (FAILED(hr)) return;

	// �����_�[�^�[�Q�b�g�r���[�쐬
	ID3D11Texture2D* renderTarget{};
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	if (renderTarget != nullptr)m_Device->CreateRenderTargetView(renderTarget, NULL, &m_RenderTargetView);
	renderTarget->Release();

	// �f�v�X�X�e���V���o�b�t�@�쐬
	ID3D11Texture2D* depthStencile{};
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;   // �o�b�t�@�̕����X���b�v�`�F�[���ɍ��킹��
	textureDesc.Height = swapChainDesc.BufferDesc.Height; // �o�b�t�@�̍������X���b�v�`�F�[���ɍ��킹��
	textureDesc.MipLevels = 1;                            // �~�b�v���x����1�i�~�b�v�}�b�v�͎g�p���Ȃ��j
	textureDesc.ArraySize = 1;                            // �e�N�X�`���̔z��T�C�Y�i�ʏ�1�j
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;           // �t�H�[�}�b�g��16�r�b�g�̐[�x�o�b�t�@���g�p
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;    // �X���b�v�`�F�[���Ɠ����T���v���ݒ�
	textureDesc.Usage = D3D11_USAGE_DEFAULT;              // �g�p���@�̓f�t�H���g�iGPU�Ŏg�p�j
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;     // �[�x�X�e���V���o�b�t�@�Ƃ��Ďg�p
	textureDesc.CPUAccessFlags = 0;                       // CPU����̃A�N�Z�X�͕s�v
	textureDesc.MiscFlags = 0;                            // ���̑��̃t���O�͐ݒ�Ȃ�

	hr = m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);
	if (FAILED(hr)) return;

	// �f�v�X�X�e���V���r���[�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format; // �f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g��ݒ�
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // �r���[�̎�����2D�e�N�X�`���Ƃ��Đݒ�i2D�e�N�X�`���p�̃f�v�X�X�e���V���r���[�j
	depthStencilViewDesc.Flags = 0; // ���ʂȃt���O�͐ݒ肵�Ȃ��i�f�t�H���g�̓���j
	if (depthStencile != nullptr)m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthStencilView);
	depthStencile->Release();

	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView); // �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���r���[��ݒ�

	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)Application::GetWidth();   // �r���[�|�[�g�̕�
	viewport.Height = (FLOAT)Application::GetHeight(); // �r���[�|�[�g�̍���
	viewport.MinDepth = 0.0f;                          // �[�x�͈͂̍ŏ��l
	viewport.MaxDepth = 1.0f;                          // �[�x�͈͂̍ő�l
	viewport.TopLeftX = 0;                             // �r���[�|�[�g�̍������X���W
	viewport.TopLeftY = 0;                             // �r���[�|�[�g�̍������Y���W�j
	m_DeviceContext->RSSetViewports(1, &viewport);

	
	// ���X�^���C�U�X�e�[�g�ݒ�
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	//rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	//rasterizerDesc.CullMode = D3D11_CULL_NONE;
	//rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;

	ID3D11RasterizerState* rs;
	hr = m_Device->CreateRasterizerState(&rasterizerDesc, &rs);
	if (FAILED(hr)) return;

	m_DeviceContext->RSSetState(rs);

	// �u�����h �X�e�[�g����
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));                   // BlendDesc�\���̂��[���ŏ��������A���������N���A
	BlendDesc.AlphaToCoverageEnable = FALSE;                     // �A���t�@�E�g�D�E�J�o���b�W�𖳌����i�����x���J�o���b�W�Ƃ��ė��p���Ȃ��j
	BlendDesc.IndependentBlendEnable = TRUE;                     // �e�����_�[�^�[�Q�b�g�ɑ΂��Čʂ̃u�����h�ݒ��L����
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;               // �u�����h�𖳌��ɐݒ�i�s�����ȕ`��j
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;  // �\�[�X�i�`�悷��s�N�Z���j�̃A���t�@�l���g�p
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // �f�X�e�B�l�[�V�����i�����̃s�N�Z���j�̋t�A���t�@�l���g�p
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;      // �\�[�X�ƃf�X�e�B�l�[�V���������Z���鑀��
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;   // �\�[�X�̃A���t�@�l�����̂܂܎g�p
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; // �f�X�e�B�l�[�V�����̃A���t�@�l�𖳎�
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; // �A���t�@�l�ɑ΂��ĉ��Z������s��
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // �����_�[�^�[�Q�b�g�̃J���[�`�����l���������݃}�X�N

	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[0]);
	if (FAILED(hr)) return;

	// �u�����h �X�e�[�g���� (�A���t�@ �u�����h�p)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[1]);
	if (FAILED(hr)) return;

	// �u�����h �X�e�[�g���� (���Z�����p)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[2]);
	if (FAILED(hr)) return;

	// �u�����h �X�e�[�g���� (���Z�����p)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState[3]);
	if (FAILED(hr)) return;

	SetBlendState(BS_ALPHABLEND);


	// �f�v�X�X�e���V���X�e�[�g�ݒ�
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	hr = m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateEnable); //�[�x�L���X�e�[�g
	if (FAILED(hr)) return;

	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	hr = m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateDisable); //�[�x�����X�e�[�g
	if (FAILED(hr)) return;

	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);

	// �T���v���[�X�e�[�g�ݒ�
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 4;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState{};
	hr = m_Device->CreateSamplerState(&samplerDesc, &samplerState);
	if (FAILED(hr)) return;

	m_DeviceContext->PSSetSamplers(0, 1, &samplerState);

	// �萔�o�b�t�@����
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(Matrix);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	hr = m_Device->CreateBuffer(&bufferDesc, NULL, &m_WorldBuffer);
	m_DeviceContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);
	if (FAILED(hr)) return;

	hr = m_Device->CreateBuffer(&bufferDesc, NULL, &m_ViewBuffer);
	m_DeviceContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);
	if (FAILED(hr)) return;

	hr = m_Device->CreateBuffer(&bufferDesc, NULL, &m_ProjectionBuffer);
	m_DeviceContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);
	if (FAILED(hr)) return;
}

//=======================================
//�I������
//=======================================
void Renderer::Uninit()
{
	m_WorldBuffer->Release();
	m_ViewBuffer->Release();
	m_ProjectionBuffer->Release();

	m_DeviceContext->ClearState();
	m_RenderTargetView->Release();
	m_SwapChain->Release();
	m_DeviceContext->Release();
	m_Device->Release();

}

//=======================================
//�`��J�n
//=======================================
void Renderer::Begin()
{
	float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, clearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//=======================================
//�`��I��
//=======================================
void Renderer::End()
{
	m_SwapChain->Present(1, 0);
}

//=======================================
// �[�x�X�e���V���̗L���E������ݒ�
//=======================================
void Renderer::SetDepthEnable(bool Enable)
{
	if (Enable) 
	{
		// �[�x�e�X�g��L���ɂ���X�e���V���X�e�[�g���Z�b�g
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);
	}
	else
	{
		// �[�x�e�X�g�𖳌��ɂ���X�e���V���X�e�[�g���Z�b�g
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateDisable, NULL);
	}
}

//=======================================
// �A���t�@�e�X�g�ƃJ�o���b�W�iATC�j�̗L���E������ݒ�
//=======================================
void Renderer::SetATCEnable(bool Enable)
{
	// �u�����h�t�@�N�^�[�i�����x�Ȃǂ̒����Ɏg�p�j
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
	{
		// �A���t�@�e�X�g�ƃJ�o���b�W (ATC) ��L���ɂ���u�����h�X�e�[�g���Z�b�g
		m_DeviceContext->OMSetBlendState(m_BlendStateATC, blendFactor, 0xffffffff);
	}
	else 
	{
		// �ʏ�̃u�����h�X�e�[�g���Z�b�g
		m_DeviceContext->OMSetBlendState(m_BlendState[0], blendFactor, 0xffffffff);
	}
}

//=======================================
//
//=======================================
void Renderer::SetWorldViewProjection2D()
{
	Matrix world = Matrix::Identity;			// �P�ʍs��ɂ���
	world = world.Transpose();			// �]�u
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

	Matrix view = Matrix::Identity;			// �P�ʍs��ɂ���
	view = view.Transpose();			// �]�u
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

	// 2D�`������㌴�_�ɂ���
	Matrix projection = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,
		static_cast<float>(Application::GetWidth()),	// �r���[�{�����[���̍ŏ��w
		static_cast<float>(Application::GetHeight()),	// �r���[�{�����[���̍ŏ��x
		0.0f,											// �r���[�{�����[���̍ő�x
		0.0f,
		1.0f);

	projection = projection.Transpose();

	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}

//=======================================
// ���[���h�s���ݒ�
//=======================================
void Renderer::SetWorldMatrix(Matrix* WorldMatrix)
{
	Matrix world;
	world = WorldMatrix->Transpose(); // �]�u

	// ���[���h�s���GPU���֑���
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
}

//=======================================
// �r���[�s���ݒ�
//=======================================
void Renderer::SetViewMatrix(Matrix* ViewMatrix)
{
	Matrix view;
	view = ViewMatrix->Transpose(); // �]�u

	// �r���[�s���GPU���֑���
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
}

//=======================================
// �v���W�F�N�V�����s���ݒ�
//=======================================
void Renderer::SetProjectionMatrix(Matrix* ProjectionMatrix)
{
	Matrix projection;
	projection = ProjectionMatrix->Transpose(); // �]�u

	// �v���W�F�N�V�����s���GPU���֑���
	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}

//=======================================
//���_�V�F�[�_�[�쐬
//=======================================
void Renderer::CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName)
{
	FILE* file; // �t�@�C�����J�����߂̃|�C���^
	long int fsize; // �t�@�C���T�C�Y���i�[����ϐ�
	fopen_s(&file, FileName, "rb"); // �V�F�[�_�[�t�@�C����ReadBinary���[�h�ŊJ��
	assert(file); // �t�@�C��������ɊJ�������ǂ������m�F

	fsize = _filelength(_fileno(file)); // �t�@�C���̃T�C�Y���擾
	unsigned char* buffer = new unsigned char[fsize]; // �t�@�C���T�C�Y�Ɋ�Â��ăo�b�t�@���m��
	fread(buffer, fsize, 1, file); // �t�@�C������o�b�t�@�Ƀf�[�^��ǂݍ���
	fclose(file); // �ǂݍ��݊�����A�t�@�C�������

	// �f�o�C�X���g���Ē��_�V�F�[�_�[���쐬
	m_Device->CreateVertexShader(buffer, fsize, NULL, VertexShader);

	// ���_���C�A�E�g�i���̓��C�A�E�g�j�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// ���_�̈ʒu���i3��float�l�j
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,		D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// ���_�̖@���x�N�g�����i3��float�l�j
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	4 * 3,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// ���_�̐F���i4��float�l�FRGBA�j
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	4 * 6,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// ���_�̃e�N�X�`�����W���i2��float�l�j
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0,	4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout); // ���C�A�E�g�̗v�f�����擾

	// �f�o�C�X���g���Ē��_���C�A�E�g���쐬
	m_Device->CreateInputLayout(layout, numElements, buffer, fsize, VertexLayout);

	delete[] buffer; // �o�b�t�@�̃����������
}

//=======================================
//�s�N�Z���V�F�[�_�[�쐬
//=======================================
void Renderer::CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName)
{
	FILE* file; // �t�@�C�����J�����߂̃|�C���^
	long int fsize; // �t�@�C���T�C�Y���i�[����ϐ�
	fopen_s(&file, FileName, "rb"); // �V�F�[�_�[�t�@�C����ReadBinary���[�h�ŊJ��
	assert(file); // �t�@�C��������ɊJ�������ǂ������m�F

	fsize = _filelength(_fileno(file)); // �t�@�C���̃T�C�Y���擾
	unsigned char* buffer = new unsigned char[fsize]; // �t�@�C���T�C�Y�Ɋ�Â��ăo�b�t�@���m��
	fread(buffer, fsize, 1, file); // �t�@�C������o�b�t�@�Ƀf�[�^��ǂݍ���
	fclose(file); // �ǂݍ��݊�����A�t�@�C�������

	// �f�o�C�X���g���ăs�N�Z���V�F�[�_�[���쐬
	m_Device->CreatePixelShader(buffer, fsize, NULL, PixelShader);
	
	delete[] buffer; // �o�b�t�@�̃����������
}