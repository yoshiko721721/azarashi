/*#pragma once
#include "direct3d.h"
#include "SceneManager.h"
class Game
{
	SceneManager* SceneManager;//
public:
	void Init(HWND hWnd);
	void Update();
	void Draw();
	void Uninit();
	bool ShouldExit();
};*/
//-------------------------------------------------
//全体のloopを管理するためのクラス
//------------------------------------------------
#pragma once
#include <windows.h>
#include "direct3d.h"
#include "SceneManager.h"
#include "input.h"

class Game
{
    SceneManager sceneManager; // SceneManagerのインスタンスをメンバ変数として持つ
public:
    void Init(HWND hWnd);//ゲーム全体を
    void Update();
    void Draw();
    void Uninit();
    bool ShouldExit();
private:
	Input input;
};