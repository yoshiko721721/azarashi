#include"Scene.h"


//セッター
void Scene::SetCurrentScene(SceneList setScene)
{
	newScene = setScene;
}
void Scene::SetOldScene(SceneList setScene)
{
	oldScene = setScene;
}

//ゲッター
SceneList Scene::GetCurrentScene()
{
	return newScene;
}
SceneList Scene::GetOldScene()
{
	return oldScene;
}
