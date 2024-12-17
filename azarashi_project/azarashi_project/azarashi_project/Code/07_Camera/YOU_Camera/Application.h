﻿#pragma once

#include    <Windows.h>
#include    <cstdint>

//-----------------------------------------------------------------------------
// Applicationクラス
//-----------------------------------------------------------------------------
class Application
{
public:
    Application(uint32_t width, uint32_t height);
    ~Application();
    void Run();

    // 幅を取得
    static uint32_t GetWidth() {
        return m_Width;
    }

    // 高さを取得
    static uint32_t GetHeight() {
        return m_Height;
    }

    // ウインドウハンドルを返す
    static HWND GetWindow() {
        return m_hWnd;
    }

private:
    static HINSTANCE   m_hInst;        // インスタンスハンドル
    static HWND        m_hWnd;         // ウィンドウハンドル
    static uint32_t    m_Width;        // ウィンドウの横幅
    static uint32_t    m_Height;       // ウィンドウの縦幅

    static bool InitApp();
    static void TermApp();
    static bool InitWnd();
    static void TermWnd();
    static void MainLoop();

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
};