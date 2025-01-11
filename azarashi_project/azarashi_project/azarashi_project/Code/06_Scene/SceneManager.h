#pragma once
#include"Scene.h"
#include "../03_GameMainFile/Title/TitleScene.h"
#include "../03_GameMainFile/Game/GameScene.h"


class SceneManager 
{
private:
	std::vector<std::unique_ptr<Scene>> sceneList;
	std::unique_ptr<Scene> currentScene;			//���݂̃V�[��

public:
	// �V���O���g���p�^�[��
	static SceneManager& GetInstance();

	void AddScene();									//�V�[���ǉ�
	void ChangeScene(std::unique_ptr<Scene> newScene);	//�V�[���J��
	void Update();										//���݂̃V�[���̍X�V����
	void Draw();										//���݂̃V�[���̕`�揈��
	void Uninit();										//���݂̃V�[���̏I������

	bool isSceneListTogether();							//oldScene��nowScene�̔�r
														//��������ture �����Ȃ� false

};

