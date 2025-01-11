#include "SceneManager.h"
//
//	�|�����[�t�B�Y���Ŏg�p
//

//�V�[���̒ǉ�
void SceneManager::AddScene()
{
	sceneList.push_back(std::make_unique<TitleScene>());
	sceneList.push_back(std::make_unique<GameScene> ());
}

//�V�[���̐؂�ւ�
void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
	if (currentScene) {
		currentScene->Uninit();
	}
	
	currentScene = std::move(newScene); //�V�[���̈ړ�
	currentScene->Init();				// �V�[���̏��������s��
	
}

//�X�V����
void SceneManager::Update()
{

	if (currentScene)
	{
		//currentScene->input.Update();
		currentScene->Update(); 
	}

	//oldScene��newScene���r���Ĉ�v���Ȃ������ꍇchangeScene������
	if (isSceneListTogether()) {
		SceneList newBuff = currentScene->GetCurrentScene();
		switch (newBuff) {
		case TITLESCENE: ChangeScene(std::make_unique<TitleScene>());   break;
		case GAMESCENE : ChangeScene(std::make_unique<GameScene>());   break;
		default:  return;
		}
	}

}

//�`�揈��
void SceneManager::Draw()
{
	D3D_StartRender();
	
	if (currentScene) 
	{
		currentScene->Draw();
	}

	D3D_FinishRender();
}

void SceneManager::Uninit()
{
	if (currentScene) {
		currentScene->Uninit();
	}
}

bool SceneManager::isSceneListTogether()
{
	if (currentScene->GetOldScene() != currentScene->GetCurrentScene()) {
		return true;
	}
	return false;
}

// �V���O���g���̃C���X�^���X�擾
SceneManager& SceneManager::GetInstance() {
	static SceneManager instance;
	return instance;
}
