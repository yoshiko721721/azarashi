#include "SceneManager.h"

std::unique_ptr<Scene>
SceneManager::currentScene = nullptr;

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
    if (currentScene)
    {
        currentScene->Uninit();//変更前に現在のシーンのUninitを行う
    }

    currentScene = std::move(newScene); //オブジェクトの所有権を移動するための関数
                                        //newSceneの所有権をcurrentSceneに移す
    currentScene->Init();               //現在のシーンの開始の処理をするよ

}

void SceneManager::Update()
{
    if (currentScene)//ちゃんと今のシーンのデータが入っているなら
    {
        currentScene->Update();//currentSceneを参照してUpdateする
    }
}

void SceneManager::Draw()
{
    if (currentScene)//ちゃんと今のシーンのデータが入っているなら
    {
        currentScene->Draw();//currentSceneを参照してDrawする
    }
}

void SceneManager::Uninit()
{
    if (currentScene)//ちゃんと今のシーンのデータが入っているなら
    {
        currentScene->Uninit();//currentSceneを参照してUninitする
    }
}
