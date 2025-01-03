#pragma once
#include <iostream>

#include "../06_Scene/Scene.h"

class Application {
private:
	static Application* m_Instance;		//インスタンス
	Scene* m_Scene;						//シーン

	std::vector<std::unique_ptr<Object>> m_Objects; // オブジェクト

public:
	Application();
	static void Init(HWND hWnd);	//初期化
	static void Update(void);		//更新
	static void Draw();			//描画
	static void Uninit();			//終了

	static Application* GetInstance();

	void ChangeScene(SceneList sName); // シーンを変更
	void DeleteObject(Object* pt); // オブジェクトを削除する
	void DeleteAllObject(); // オブジェクトをすべて削除する

	// オブジェクトを追加する(※テンプレート関数なのでここに直接記述)
	template<typename... Args> 
	Object* AddObject(Args&&... args)
	{
		auto newObject = std::make_unique<Object>(std::forward<Args>(args)...);
		Object* objectPtr = newObject.get();
		m_Objects.push_back(std::move(newObject));
		return objectPtr;
	}

	// オブジェクトを取得する(※テンプレート関数なのでここに直接記述)
	template<class T> std::vector<T*> GetObjects()
	{
		std::vector<T*> res;
		for (auto& o : m_Instance->m_Objects) {
			// dynamic_castで型をチェック
			if (T* derivedObj = dynamic_cast<T*>(o.get())) {
				res.emplace_back(derivedObj);
			}
		}
		return res;
	}

};
