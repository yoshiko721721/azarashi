#pragma once
#include <vector>
#include <memory>
#include"../01_Direct3D/direct3d.h"
#include"../01_Direct3D/Object.h"
#include"../02_Input/input.h"
#include"../02_Input/miyoshi_input/ControllerInput.h"

enum SceneList {
	TITLESCENE,
	STAGESELECTSCENE,
	GAMESCENE,
	TESTSCENE,
	TESTSCENE02,
	LOADSCENE,
	SCENENUM
};

class Scene {
private:

public:

	//Scene() {};
	//virtual ~Scene();
	//èÉêàâºëzä÷êî

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Uninit() = 0;
	

};