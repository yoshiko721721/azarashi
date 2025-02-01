#pragma once

#include <xaudio2.h>

// サウンドファイル
typedef enum
{
	SOUND_LABEL_BGM1=0,//タイトルBGM
	SOUND_LABEL_BGM2 ,//ステージBGM
	SOUND_LABEL_SE1,	//ボタン押したときの音	
	SOUND_LABEL_SE2,	//アザラシが動く音(Select)
	SOUND_LABEL_SE3,	//ボタン押したときの音
	SOUND_LABEL_SE4,	//ジャンプ案
	SOUND_LABEL_SE5,	//クリア音

	SOUND_LABEL_MAX,
} SOUND_LABEL;

class Sound {
private:
	// パラメータ構造体
	typedef struct
	{
		LPCSTR filename;	// 音声ファイルまでのパスを設定
		bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
	} PARAM;

	PARAM m_param[SOUND_LABEL_MAX] =
	{
		{"Asset/sound/BGM/Title_Stageselect.wav", true},
		{"Asset/sound/BGM/stage.wav", true},
		{"Asset/sound/SE/Cursor_Select.wav", false},
		{"Asset/sound/SE/Cursor_Move.wav", false},
		{"Asset/sound/SE/Press_Any_Button.wav", false},
		{"Asset/sound/SE/Jump.wav", false},
		{"Asset/sound/SE/軽いノリのアイキャッチ.wav", false},
	};

	IXAudio2* m_pXAudio2 = NULL;
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;
	IXAudio2SourceVoice* m_pSourceVoice[SOUND_LABEL_MAX];
	WAVEFORMATEXTENSIBLE m_wfx[SOUND_LABEL_MAX]; // WAVフォーマット
	XAUDIO2_BUFFER m_buffer[SOUND_LABEL_MAX];
	BYTE* m_DataBuffer[SOUND_LABEL_MAX];

	HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
	HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

public:
	// ゲームループ開始前に呼び出すサウンドの初期化処理
	HRESULT Init(void);

	// ゲームループ終了後に呼び出すサウンドの解放処理
	void Uninit(void);

	// 引数で指定したサウンドを再生する
	void Play(SOUND_LABEL label);

	// 引数で指定したサウンドを停止する
	void Stop(SOUND_LABEL label);

	// 引数で指定したサウンドの再生を再開する
	void Resume(SOUND_LABEL label);
};