#pragma once

#include "Scene.h"

class StageSelectScene : public Scene {
private:
    int selectedStage;  // 現在選択中のステージ
    int totalStages;    // ステージの総数

public:
    StageSelectScene();              // コンストラクタ
    ~StageSelectScene();             // デストラクタ

    void Update() override;          // ステージセレクトの更新処理
    void Draw() override;          // ステージセレクトの描画処理
};
