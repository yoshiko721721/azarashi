#include "StageSelectScene.h"
#include "../../06_Scene/SceneManager.h"
#include "../../02_Input/input.h"

#include <iostream>

#include "../../03_GameMainFile/Title/TitleScene.h"
#include "../../03_GameMainFile/Game/GameScene.h"
#include "../../03_GameMainFile/Application.h"


// �R���X�g���N�^
StageSelectScene::StageSelectScene()
    : selectedStage(0), totalStages(5) { // �X�e�[�W����
    std::cout << "StageSelectScene ������" << std::endl;
}

// �f�X�g���N�^
StageSelectScene::~StageSelectScene() {
    std::cout << "StageSelectScene �폜" << std::endl;
}

//����������
void StageSelectScene::Init() {



}

// �X�V����
void StageSelectScene::Update() {
    std::cout << "StageSelectScene Update" << std::endl;

    // �v���C���[�̓��͂��`�F�b�N
    if (XINPUT_RIGHT)
    {
        selectedStage = (selectedStage - 1 + totalStages) % totalStages;
    }
    else if (XINPUT_LEFT) {
        selectedStage = (selectedStage + 1) % totalStages;
    }
    else if (XINPUT_A) {
        std::cout << "Stage " << selectedStage + 1 << " Selected" << std::endl;
        Application::GetInstance()->ChangeScene(SceneList::GAMESCENE);
    }
}

// �`�揈��
void StageSelectScene::Draw() {
    std::cout << "StageSelectScene�`��" << std::endl;

    // �X�e�[�W�I����UI��`��
    for (int i = 0; i < totalStages; i++) {
        if (i == selectedStage) {
            std::cout << "> Stage " << i + 1 << " <" << std::endl;  // �I�𒆂̃X�e�[�W
        }
        else {
            std::cout << "  Stage " << i + 1 << std::endl;          // ���̃X�e�[�W
        }
    }
}

void StageSelectScene::Uninit() {

}