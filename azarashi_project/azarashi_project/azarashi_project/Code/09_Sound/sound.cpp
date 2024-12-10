#include "sound.h"

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

//=============================================================================
// 初期化
//=============================================================================
HRESULT Sound::Init()
{
    HRESULT hr = S_OK;

    HANDLE hFile;
    DWORD dwChunkSize;
    DWORD dwChunkPosition;
    DWORD filetype;

    // COMの初期化
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        return hr;
    }

    /**** Create XAudio2 ****/
    hr = XAudio2Create(&m_pXAudio2, 0);
    if (FAILED(hr)) {
        CoUninitialize();
        return hr;
    }

    /**** Create Mastering Voice ****/
    hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
    if (FAILED(hr)) {
        m_pXAudio2->Release();
        CoUninitialize();
        return hr;
    }

    /**** Initialize Sound ****/
    for (int i = 0; i < SOUND_LABEL_MAX; i++)
    {
        memset(&m_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));
        memset(&m_buffer[i], 0, sizeof(XAUDIO2_BUFFER));

        hFile = CreateFileA(m_param[i].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, 0, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            hr = HRESULT_FROM_WIN32(GetLastError());
            // Cleanup
            Uninit();
            return hr;
        }

        if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
            hr = HRESULT_FROM_WIN32(GetLastError());
            CloseHandle(hFile);
            // Cleanup
            Uninit();
            return hr;
        }

        // Check the file type
        if (FAILED(FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition)) ||
            FAILED(ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition)) ||
            filetype != fourccWAVE) {
            CloseHandle(hFile);
            // Cleanup
            Uninit();
            return S_FALSE;
        }

        // Read "fmt " chunk
        if (FAILED(FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition)) ||
            FAILED(ReadChunkData(hFile, &m_wfx[i], dwChunkSize, dwChunkPosition))) {
            CloseHandle(hFile);
            // Cleanup
            Uninit();
            return S_FALSE;
        }

        // Read "data" chunk
        if (FAILED(FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition))) {
            CloseHandle(hFile);
            // Cleanup
            Uninit();
            return S_FALSE;
        }

        m_DataBuffer[i] = new BYTE[dwChunkSize];
        if (FAILED(ReadChunkData(hFile, m_DataBuffer[i], dwChunkSize, dwChunkPosition))) {
            CloseHandle(hFile);
            delete[] m_DataBuffer[i];
            // Cleanup
            Uninit();
            return S_FALSE;
        }

        CloseHandle(hFile);

        // Set buffer
        m_buffer[i].AudioBytes = dwChunkSize;
        m_buffer[i].pAudioData = m_DataBuffer[i];
        m_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
        m_buffer[i].LoopCount = m_param[i].bLoop ? XAUDIO2_LOOP_INFINITE : 0;

        hr = m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[i], &(m_wfx[i].Format));
        if (FAILED(hr)) {
            // Cleanup
            Uninit();
            return hr;
        }

        hr = m_pSourceVoice[i]->SubmitSourceBuffer(&m_buffer[i]);
        if (FAILED(hr)) {
            // Cleanup
            Uninit();
            return hr;
        }
    }

    return hr;
}

//=============================================================================
// 開放処理
//=============================================================================
void Sound::Uninit(void)
{
    for (int i = 0; i < SOUND_LABEL_MAX; i++)
    {
        if (m_pSourceVoice[i])
        {
            m_pSourceVoice[i]->Stop(0);
            m_pSourceVoice[i]->FlushSourceBuffers();
            m_pSourceVoice[i]->DestroyVoice();
            m_pSourceVoice[i] = NULL;
        }

        delete[] m_DataBuffer[i];
        m_DataBuffer[i] = NULL;
    }

    if (m_pMasteringVoice)
    {
        m_pMasteringVoice->DestroyVoice();
        m_pMasteringVoice = NULL;
    }

    if (m_pXAudio2)
    {
        m_pXAudio2->Release();
        m_pXAudio2 = NULL;
    }

    CoUninitialize();
}


//=============================================================================
// 再生
//=============================================================================
void Sound::Play(SOUND_LABEL label)
{
    IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)label];

    if (pSV != nullptr)
    {
        pSV->DestroyVoice();
        pSV = nullptr;
    }

    // ソースボイス作成
    m_pXAudio2->CreateSourceVoice(&pSV, &(m_wfx[(int)label].Format));
    pSV->SubmitSourceBuffer(&(m_buffer[(int)label]));	// ボイスキューに新しいオーディオバッファーを追加

    // 再生
    pSV->Start(0);

}

//=============================================================================
// 停止
//=============================================================================
void Sound::Stop(SOUND_LABEL label)
{
    if (m_pSourceVoice[(int)label] == NULL) return;

    XAUDIO2_VOICE_STATE xa2state;
    m_pSourceVoice[(int)label]->GetState(&xa2state);
    if (xa2state.BuffersQueued)
    {
        m_pSourceVoice[(int)label]->Stop(0);
    }
}

//=============================================================================
// 一時停止
//=============================================================================
void Sound::Resume(SOUND_LABEL label)
{
    IXAudio2SourceVoice*& pSV = m_pSourceVoice[(int)label];
    pSV->Start();
}



//=============================================================================
// ユーティリティ関数群
//=============================================================================
HRESULT Sound::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());
    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;
    while (hr == S_OK)
    {
        DWORD dwRead;
        if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());
        if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());
        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                hr = HRESULT_FROM_WIN32(GetLastError());
            break;
        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
                return HRESULT_FROM_WIN32(GetLastError());
        }
        dwOffset += sizeof(DWORD) * 2;
        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }
        dwOffset += dwChunkDataSize;
        if (bytesRead >= dwRIFFDataSize) return S_FALSE;
    }
    return S_OK;
}

HRESULT Sound::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());
    DWORD dwRead;
    if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
        hr = HRESULT_FROM_WIN32(GetLastError());
    return hr;
}
