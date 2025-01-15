#pragma once

#include "Scene.h"

class StageSelectScene : public Scene {
private:
    int selectedStage;  // ���ݑI�𒆂̃X�e�[�W
    int totalStages;    // �X�e�[�W�̑���

public:
    StageSelectScene();              // �R���X�g���N�^
    ~StageSelectScene();             // �f�X�g���N�^

    void Init();                     //����������
    void Update() override;          // �X�V����
    void Draw() override;            // �`�揈��
    void Uninit();                   // �I������
};
