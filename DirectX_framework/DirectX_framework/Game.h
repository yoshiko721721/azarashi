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
//�S�̂�loop���Ǘ����邽�߂̃N���X
//------------------------------------------------
#pragma once
#include <windows.h>
#include "direct3d.h"
#include "SceneManager.h"
#include "input.h"

class Game
{
    SceneManager sceneManager; // SceneManager�̃C���X�^���X�������o�ϐ��Ƃ��Ď���
public:
    void Init(HWND hWnd);//�Q�[���S�̂�
    void Update();
    void Draw();
    void Uninit();
    bool ShouldExit();
private:
	Input input;
};