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

public:

	//Scene() {};
	//virtual ~Scene();
	//�������z�֐�

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;
	

};