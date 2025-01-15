#pragma once

#include "Scene.h"

class StageSelectScene : public Scene {
private:
    int selectedStage;  // 現在選択中のステージ
    int totalStages;    // ステージの総数

public:
    StageSelectScene();              // コンストラクタ
    ~StageSelectScene();             // デストラクタ

    void Init();                     //初期化処理
    void Update() override;          // 更新処理
    void Draw() override;            // 描画処理
    void Uninit();                   // 終了処理
};
