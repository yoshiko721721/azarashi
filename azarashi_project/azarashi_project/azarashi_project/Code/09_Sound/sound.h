#pragma once

#include <xaudio2.h>

// �T�E���h�t�@�C��
typedef enum
{
	SOUND_LABEL_BGM1=0,		
	SOUND_LABEL_SE1,			

	SOUND_LABEL_MAX,
} SOUND_LABEL;

class Sound {
private:
	// �p�����[�^�\����
	typedef struct
	{
		LPCSTR filename;	// �����t�@�C���܂ł̃p�X��ݒ�
		bool bLoop;			// true�Ń��[�v�B�ʏ�BGM��ture�ASE��false�B
	} PARAM;

	PARAM m_param[SOUND_LABEL_MAX] =
	{
		{"bgm/bgm1.wav", true},
		{"se/se1.wav", false},
	};

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX]; // WAV�t�H�[�}�b�g
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
	HRESULT Init(void);

	// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
	void Uninit(void);

	// �����Ŏw�肵���T�E���h���Đ�����
	void Play(SOUND_LABEL label);

	// �����Ŏw�肵���T�E���h���~����
	void Stop(SOUND_LABEL label);

	// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
	void Resume(SOUND_LABEL label);
};