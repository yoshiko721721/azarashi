#include"Scene.h"


//�Z�b�^�[
void Scene::SetCurrentScene(SceneList setScene)
{
	newScene = setScene;
}
void Scene::SetOldScene(SceneList setScene)
{
	oldScene = setScene;
}

//�Q�b�^�[
SceneList Scene::GetCurrentScene()
{
	return newScene;
}
SceneList Scene::GetOldScene()
{
	return oldScene;
}
