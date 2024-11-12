//------------------------------------------------
//�V�[���؂�ւ��̍ۂ̏������܂Ƃ߂�N���X
//------------------------------------------------
#pragma once
#include "GameScene.h"
#include "TitleScene.h"
//#include "Scene.h"
#include <memory>

class SceneManager {
public:
    static void ChangeScene(std::unique_ptr<Scene> newScene);
    static void Update();
    static void Draw();
    static void Uninit();
    static std::unique_ptr<Scene> currentScene;
};

