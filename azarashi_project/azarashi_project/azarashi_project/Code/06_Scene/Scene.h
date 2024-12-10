#pragma once
#include <vector>
#include <memory>
#include"../01_Direct3D/direct3d.h"
#include"../01_Direct3D/Object.h"
#include"../02_Input/input.h"

enum SceneList {
	TITLESCENE,
	GAMESCENE,
	SCENENUM
};

class Scene {
private:
	SceneList oldScene; //�g�p���̃V�[���i���݂��ߋ����܂߂�j
	SceneList newScene; //�V�����o�^����p
public:

	//Scene() {};
	//virtual ~Scene();
	//�������z�֐�
	virtual void Init  () = 0;
	virtual void Update() = 0;
	virtual void Draw  () = 0;
	virtual void Uninit() = 0;


	//���ꂼ��̃V�[��cpp�ŃV�[���J�ڂ̑�����s����悤�ɂ���
	//oldScene���A�����Ă������悤�ɂ��邽�߂̃Z�b�^�[
	void SetCurrentScene(SceneList setScene);	
	void SetOldScene(SceneList setScene);
	//SceneList�Q�̃Q�b�^�[
	SceneList GetCurrentScene();
	SceneList GetOldScene();

};