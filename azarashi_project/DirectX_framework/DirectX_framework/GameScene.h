#pragma once
#include "Scene.h"
#include "GameBackGround.h"
#include "GameCamera.h"
#include "GamePointer.h"
#include "GameBlock.h"
//Sceneクラスを継承したゲームシーンのクラス

class GameScene : public Scene  //Sceneの抽象クラスを継承する
{
public:
    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Uninit()  override;
private:
    GameBackground GameBackGround;
    GameCamera GameCamera;
    GamePointer GamePointer;
    GameBlock GameBlock;
    //std::vector<Object*> Objects; //シーン内のゲームオブジェクトリスト。
};

