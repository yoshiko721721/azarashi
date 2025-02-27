#include "StageSelectScene.h"
#include "../../06_Scene/SceneManager.h"
#include "../../02_Input/input.h"

#include <iostream>

#include "../../03_GameMainFile/Title/TitleScene.h"
#include "../../03_GameMainFile/Game/GameScene.h"
#include "../../03_GameMainFile/Application.h"


// コンストラクタ
StageSelectScene::StageSelectScene()
    : selectedStage(0), totalStages(5) { // ステージ数分
    std::cout << "StageSelectScene 初期化" << std::endl;
}

// デストラクタ
StageSelectScene::~StageSelectScene() {
    std::cout << "StageSelectScene 削除" << std::endl;
}

//初期化処理
void StageSelectScene::Init() {



}

// 更新処理
void StageSelectScene::Update() {
    std::cout << "StageSelectScene Update" << std::endl;

    // プレイヤーの入力をチェック
    if (XINPUT_RIGHT)
    {
        selectedStage = (selectedStage - 1 + totalStages) % totalStages;
    }
    else if (XINPUT_LEFT) {
        selectedStage = (selectedStage + 1) % totalStages;
    }
    else if (XINPUT_A) {
        std::cout << "Stage " << selectedStage + 1 << " Selected" << std::endl;
        Application::GetInstance()->ChangeScene(SceneList::GAMESCENE);
    }
}

// 描画処理
void StageSelectScene::Draw() {
    std::cout << "StageSelectScene描画" << std::endl;

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

void StageSelectScene::Uninit() {

}