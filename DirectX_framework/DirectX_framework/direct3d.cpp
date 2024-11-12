#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <locale.h>
#include <atltypes.h> // CRect���g�����߂̃w�b�_�[�t�@�C��
#include <io.h>
#include <stdio.h>
#include <string.h>
#include "direct3d.h"

//�v���g�^�C�v�錾
// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
HRESULT CreateVertexShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* layout, unsigned int numElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout);
// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
HRESULT CreatePixelShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3D11PixelShader** ppPixelShader);

//--------------------------------------------------------------------------------------
// �O���[�o���ϐ�
//--------------------------------------------------------------------------------------
// ��ID3D11�Ŏn�܂�|�C���^�^�̕ϐ��́A�������K�v������
ID3D11Device* g_pDevice; // �f�o�C�X��DirectX�̊e��@�\�����
// �R���e�L�X�g���`��֘A���i��@�\
ID3D11DeviceContext* g_pDeviceContext;
// �X���b�v�`�F�C�����_�u���o�b�t�@�@�\
IDXGISwapChain* g_pSwapChain;
// �����_�[�^�[�Q�b�g���`����\���@�\
ID3D11RenderTargetView* g_pRenderTargetView;
// �f�v�X�o�b�t�@
ID3D11DepthStencilView* g_pDepthStencilView;
// �C���v�b�g���C�A�E�g
ID3D11InputLayout* g_pInputLayout;
// ���_�V�F�[�_�[�I�u�W�F�N�g
ID3D11VertexShader* g_pVertexShader;
// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g
ID3D11PixelShader* g_pPixelShader;
// �T���v���[�p�ϐ�
ID3D11SamplerState* g_pSampler;
// �萔�o�b�t�@�p�ϐ�
ID3D11Buffer* g_pConstantBuffer;
// �u�����h�X�e�[�g�p�ϐ��i�A���t�@�u�����f�B���O�j
ID3D11BlendState* g_pBlendState;

//--------------------------------------------------------------------------------------
// Direct3D�̏�����������
//--------------------------------------------------------------------------------------
HRESULT D3D_Create(HWND hwnd)
{
	HRESULT  hr; // HRESULT�^�E�E�EWindows�v���O�����Ŋ֐����s�̐���/���s���󂯎��

	D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL level;
	CRect              rect;
	::GetClientRect(hwnd, &rect);

	// �f�o�C�X�A�X���b�v�`�F�[���쐬
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	::ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	// �f�o�C�X�ƃX���b�v�`�F�C���𓯎��ɍ쐬����֐��̌Ăяo��
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		pLevels,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&g_pSwapChain,
		&g_pDevice,
		&level,
		&g_pDeviceContext);
	if (FAILED(hr)) return hr; // ��̊֐��Ăяo�������s���ĂȂ���if�Ń`�F�b�N

	// �����_�[�^�[�Q�b�g�r���[�쐬
	ID3D11Texture2D* renderTarget;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	if (FAILED(hr)) return hr;
	hr = g_pDevice->CreateRenderTargetView(renderTarget, NULL, &g_pRenderTargetView);
	renderTarget->Release();
	if (FAILED(hr)) return hr;

	// �f�v�X�X�e���V���o�b�t�@�쐬
	// ���i�f�v�X�o�b�t�@ = �[�x�o�b�t�@ = Z�o�b�t�@�j�����s�𔻒肵�đO��֌W�𐳂����`��ł���
	ID3D11Texture2D* depthStencile;
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	hr = g_pDevice->CreateTexture2D(&textureDesc, NULL, &depthStencile);
	if (FAILED(hr)) return hr;

	// �f�v�X�X�e���V���r���[�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	hr = g_pDevice->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &g_pDepthStencilView);
	if (FAILED(hr)) return hr;
	depthStencile->Release();

	// �r���[�|�[�g���쐬�i����ʕ����ȂǂɎg���A�`��̈�̎w��̂��Ɓj
	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT)rect.Width();
	viewport.Height = (FLOAT)rect.Height();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	g_pDeviceContext->RSSetViewports(1, &viewport);

	// �C���v�b�g���C�A�E�g�쐬
	D3D11_INPUT_ELEMENT_DESC layout[]
	{
		// �ʒu���W������Ƃ������Ƃ�`����
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// �F��񂪂���Ƃ������Ƃ�`����
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// UV���W
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	hr = CreateVertexShader(g_pDevice, "VertexShader.hlsl", "vs_main", "vs_5_0",
		layout, numElements, &g_pVertexShader, &g_pInputLayout);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateVertexShader error", "error", MB_OK);
		return E_FAIL;
	}

	// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
	hr = CreatePixelShader(g_pDevice, "PixelShader.hlsl", "ps_main", "ps_5_0", &g_pPixelShader);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreatePixelShader error", "error", MB_OK);
		return E_FAIL;
	}

	// �T���v���[�쐬
	// ���@�e�N�X�`�����|���S���ɓ\��Ƃ��ɁA�g��k�������ۂ̃A���S���Y��
	D3D11_SAMPLER_DESC smpDesc;
	::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = g_pDevice->CreateSamplerState(&smpDesc, &g_pSampler);
	if (FAILED(hr)) return hr;

	// �萔�o�b�t�@�쐬
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	hr = g_pDevice->CreateBuffer(&cbDesc, NULL, &g_pConstantBuffer);
	if (FAILED(hr)) return hr;

	// �u�����h�X�e�[�g�쐬 �����ߏ�������Z�������\�ɂ���F�̍������@
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = FALSE;
	BlendState.IndependentBlendEnable = FALSE;
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = g_pDevice->CreateBlendState(&BlendState, &g_pBlendState);
	if (FAILED(hr)) return hr;

	//�[�x�e�X�g�𖳌��ɂ���
	ID3D11DepthStencilState* pDSState;
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.DepthEnable = FALSE; // �[�x�e�X�g�𖳌��ɂ���
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	hr = g_pDevice->CreateDepthStencilState(&dsDesc, &pDSState);
	if (FAILED(hr)) return hr;
	g_pDeviceContext->OMSetDepthStencilState(pDSState, 1);


	return S_OK;
}

//--------------------------------------------------------------------------------------
// Direct3D�̕`�������
//--------------------------------------------------------------------------------------
void D3D_StartRender()
{
	// ��ʓh��Ԃ��F
	float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //red,green,blue,alpha

	// �`���̃L�����o�X�Ǝg�p����[�x�o�b�t�@���w�肷��
	g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);
	// �`���L�����o�X��h��Ԃ�
	g_pDeviceContext->ClearRenderTargetView(g_pRenderTargetView, clearColor);
	// �[�x�o�b�t�@�����Z�b�g����
	g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	g_pDeviceContext->IASetInputLayout(g_pInputLayout);
	g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	g_pDeviceContext->VSSetShader(g_pVertexShader, NULL, 0);
	g_pDeviceContext->PSSetShader(g_pPixelShader, NULL, 0);

	// �T���v���[���s�N�Z���V�F�[�_�[�ɓn��
	g_pDeviceContext->PSSetSamplers(0, 1, &g_pSampler);

	// �萔�o�b�t�@�𒸓_�V�F�[�_�[�ɃZ�b�g����
	g_pDeviceContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);

	//�u�����h�X�e�[�g���Z�b�g����
	g_pDeviceContext->OMSetBlendState(g_pBlendState, NULL, 0xffffffff);
}

void D3D_FinishRender()
{
	// �_�u���o�b�t�@�̐؂�ւ����s����ʂ��X�V����
	g_pSwapChain->Present(0, 0);
}

//--------------------------------------------------------------------------------------
// Direct3D�̉���i�I�������j������
//--------------------------------------------------------------------------------------
// ��DirectX�̊e�@�\�͍쐬������A�A�v���I�����ɕK��������Ȃ���΂Ȃ�Ȃ�
void D3D_Release()
{
	if (g_pDeviceContext) g_pDeviceContext->ClearState();
	SAFE_RELEASE(g_pBlendState);
	SAFE_RELEASE(g_pConstantBuffer);
	SAFE_RELEASE(g_pSampler);
	SAFE_RELEASE(g_pPixelShader);
	SAFE_RELEASE(g_pVertexShader);
	SAFE_RELEASE(g_pInputLayout);
	SAFE_RELEASE(g_pDepthStencilView);
	SAFE_RELEASE(g_pRenderTargetView);
	SAFE_RELEASE(g_pSwapChain);
	SAFE_RELEASE(g_pDeviceContext);
	SAFE_RELEASE(g_pDevice);
}

//--------------------------------------------------------------------------------------
// �V�F�[�_�[���t�@�C���g���q�ɍ��킹�ăR���p�C��
//--------------------------------------------------------------------------------------
HRESULT CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut)
{
	*ppBlobOut = nullptr;
	int aaa = strlen(szFileName);
	//�g���q��hlsl����cso�ɕύX�����t�@�C�������쐬
	char* csoFileName = new char[strlen(szFileName)];
	const char* dot = strrchr(szFileName, '.'); // �Ō��"."��T��
	if (dot != NULL) {
		size_t prefixLength = dot - szFileName;
		strncpy_s(csoFileName, prefixLength + 1, szFileName, _TRUNCATE); // �g���q�ȊO���R�s�[
		strcpy_s(csoFileName + prefixLength, 5, ".cso"); // �V�����g���q��ǉ�
	}
	else {
		strcpy_s(csoFileName, strlen(szFileName), szFileName); // �g���q���Ȃ��ꍇ�͂��̂܂܃R�s�[
	}

	FILE* fp;
	// �R���p�C���ς݃V�F�[�_�[�t�@�C��(cso)������Γǂݍ���
	if (fopen_s(&fp, csoFileName, "rb") == 0)
	{
		long int size = _filelength(_fileno(fp));
		unsigned char* buffer = new unsigned char[size];
		fread(buffer, size, 1, fp);
		if (!buffer) return E_FAIL;
		*ShaderObject = buffer;
		ShaderObjectSize = size;
		fclose(fp);
	}
	// �R���p�C���ς݃V�F�[�_�[�t�@�C����������΃V�F�[�_�[�t�@�C��(hlsl)���R���p�C������
	else
	{
		ID3DBlob* p1 = nullptr;
		HRESULT hr = S_OK;
		WCHAR	filename[512];
		size_t 	wLen = 0;
		int err = 0;

		// char -> wchar�ɕϊ�
		setlocale(LC_ALL, "japanese");
		err = mbstowcs_s(&wLen, filename, 512, szFileName, _TRUNCATE);

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		// D3DCOMPILE_DEBUG�t���O��ݒ肷��ƁA�V�F�[�_�[�Ƀf�o�b�O��񂪖��ߍ��܂��
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* pErrorBlob = nullptr;
		hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
		if (FAILED(hr))
		{
			if (pErrorBlob != nullptr) {
				MessageBoxA(NULL, (char*)pErrorBlob->GetBufferPointer(), "Error", MB_OK);
			}
			if (pErrorBlob) pErrorBlob->Release();
			if (*ppBlobOut)(*ppBlobOut)->Release();
			return hr;
		}
		if (pErrorBlob) pErrorBlob->Release();

		*ShaderObject = (*ppBlobOut)->GetBufferPointer();
		ShaderObjectSize = (*ppBlobOut)->GetBufferSize();
	}

	delete[] csoFileName;
	return S_OK;
}

//--------------------------------------------------------------------------------------
// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐�����
//--------------------------------------------------------------------------------------
HRESULT CreateVertexShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* layout, unsigned int numElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout)
{
	HRESULT   hr;
	ID3DBlob* pBlob = nullptr;
	void* ShaderObject;
	size_t	  ShaderObjectSize;

	// �t�@�C���̊g���q�ɍ��킹�ăR���p�C��
	hr = CompileShader(szFileName, szEntryPoint, szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return E_FAIL;
	}

	// ���_�V�F�[�_�[�𐶐�
	hr = device->CreateVertexShader(ShaderObject, ShaderObjectSize, NULL, ppVertexShader);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return E_FAIL;
	}

	// ���_�f�[�^��`����
	hr = device->CreateInputLayout(
		layout,
		numElements,
		ShaderObject,
		ShaderObjectSize,
		ppVertexLayout);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateInputLayout error", "error", MB_OK);
		pBlob->Release();
		return E_FAIL;
	}

	return S_OK;
}

//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�����
//--------------------------------------------------------------------------------------
HRESULT CreatePixelShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3D11PixelShader** ppPixelShader)
{
	HRESULT   hr;
	ID3DBlob* pBlob = nullptr;
	void* ShaderObject;
	size_t	  ShaderObjectSize;

	// �t�@�C���̊g���q�ɍ��킹�ăR���p�C��
	hr = CompileShader(szFileName, szEntryPoint, szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// �s�N�Z���V�F�[�_�[�𐶐�
	hr = device->CreatePixelShader(ShaderObject, ShaderObjectSize, NULL, ppPixelShader);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return E_FAIL;
	}

	return S_OK;
}
