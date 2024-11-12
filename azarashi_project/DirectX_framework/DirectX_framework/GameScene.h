#pragma once
#include "Scene.h"
#include "GameBackGround.h"
#include "GameCamera.h"
#include "GamePointer.h"
#include "GameBlock.h"
//Scene�N���X���p�������Q�[���V�[���̃N���X

class GameScene : public Scene  //Scene�̒��ۃN���X���p������
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
    //std::vector<Object*> Objects; //�V�[�����̃Q�[���I�u�W�F�N�g���X�g�B
};

