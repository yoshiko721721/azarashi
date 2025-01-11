#include "StageSelectScene.h"
#include "SceneManager.h"
#include "input.h"
#include <iostream>

#include "../03_GameMainFile/Game/GameScene.h"


// コンストラクタ
StageSelectScene::StageSelectScene()
    : selectedStage(0), totalStages(5) { // ステージ数分
    std::cout << "StageSelectScene Initialized" << std::endl;
}

// デストラクタ
StageSelectScene::~StageSelectScene() {
    std::cout << "StageSelectScene Destroyed" << std::endl;
}

// 更新処理
void StageSelectScene::Update() {
    std::cout << "StageSelectScene Update" << std::endl;

    // プレイヤーの入力をチェック
    if (XINPUT_RIGHT) {
        selectedStage = (selectedStage - 1 + totalStages) % totalStages;
    }
    else if (XINPUT_LEFT) {
        selectedStage = (selectedStage + 1) % totalStages;
    }
    else if (XINPUT_A) {
        std::cout << "Stage " << selectedStage + 1 << " Selected" << std::endl;
        SceneManager::GetInstance().ChangeScene(Scene::GameScene);
    }
}

// 描画処理
void StageSelectScene::Draw() {
    std::cout << "Rendering StageSelectScene" << std::endl;

    // ステージ選択のUIを描画
    for (int i = 0; i < totalStages; i++) {
        if (i == selectedStage) {
            std::cout << "> Stage " << i + 1 << " <" << std::endl;  // 選択中のステージ
        }
        else {
            std::cout << "  Stage " << i + 1 << std::endl;          // 他のステージ
        }
    }
}