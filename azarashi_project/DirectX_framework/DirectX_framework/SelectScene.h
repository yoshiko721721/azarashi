#pragma once
#include "Scene.h"
#include "GameCamera.h"
//Sceneクラスを継承したゲームシーンのクラス

class SelectScene : public Scene  //Sceneの抽象クラスを継承する
{
public:
    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Uninit()  override;
private:
    
    //std::vector<Object*> Objects; //シーン内のゲームオブジェクトリスト。
};
