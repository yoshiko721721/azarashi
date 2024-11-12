#pragma once
#include "Scene.h"
#include "TitleBackGround.h"
#include "TitleCamera.h"
//Scene�N���X���p�������Q�[���V�[���̃N���X

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