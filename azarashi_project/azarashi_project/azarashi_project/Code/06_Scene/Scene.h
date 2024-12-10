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
	SceneList oldScene; //使用中のシーン（現在も過去も含める）
	SceneList newScene; //新しく登録する用
public:

	//Scene() {};
	//virtual ~Scene();
	//純粋仮想関数
	virtual void Init  () = 0;
	virtual void Update() = 0;
	virtual void Draw  () = 0;
	virtual void Uninit() = 0;


	//それぞれのシーンcppでシーン遷移の操作を行えるようにする
	//oldSceneも連動していじれるようにするためのセッター
	void SetCurrentScene(SceneList setScene);	
	void SetOldScene(SceneList setScene);
	//SceneList２つのゲッター
	SceneList GetCurrentScene();
	SceneList GetOldScene();

};