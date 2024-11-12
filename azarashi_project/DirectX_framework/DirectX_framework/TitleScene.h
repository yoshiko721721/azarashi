#pragma once
#include "Scene.h"
#include "TitleBackGround.h"
#include "TitleCamera.h"
//Sceneクラスを継承したゲームシーンのクラス

class TitleScene : public Scene 
{
public:
    void Init()     override;
    void Update()   override;
    void Draw()     override;
    void Uninit()   override;

    TitleBackground TitleBackground;
    TitleCamera TitleCamera;
};