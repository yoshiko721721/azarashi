#pragma once
#include "Scene.h"
#include "GameCamera.h"
//Scene�N���X���p�������Q�[���V�[���̃N���X

class SelectScene : public Scene  //Scene�̒��ۃN���X���p������
{
public:
    void Init()    override;
    void Update()  override;
    void Draw()    override;
    void Uninit()  override;
private:
    
    //std::vector<Object*> Objects; //�V�[�����̃Q�[���I�u�W�F�N�g���X�g�B
};
