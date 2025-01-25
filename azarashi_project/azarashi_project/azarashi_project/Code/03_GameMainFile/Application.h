#pragma once
#include <iostream>
#include "../02_Input/miyoshi_input/ControllerInput.h"
#include "../06_Scene/Scene.h"


class Application {
private:
	static Application* m_Instance;		//�C���X�^���X
	Scene* m_Scene;						//�V�[��

	std::vector<std::unique_ptr<Object>> m_Objects; // �I�u�W�F�N�g

	bool isFirstTimeOpening = true;

public:
	Application();
	static void Init(HWND hWnd);	//������
	static void Update(void);		//�X�V
	static void Draw();			//�`��
	static void Uninit();			//�I��

	static Application* GetInstance();

	void ChangeScene(SceneList sName); // �V�[����ύX
	void DeleteObject(Object* pt); // �I�u�W�F�N�g���폜����
	void DeleteAllObject(); // �I�u�W�F�N�g�����ׂč폜����
	Scene* GetCurrentScene();
	bool GetisFirstOpening()
	{
		return isFirstTimeOpening = true;
	}
	void SetisFirstOpening(bool isFirst)
	{
		isFirstTimeOpening = isFirst;
	}

	// �I�u�W�F�N�g��ǉ�����(���e���v���[�g�֐��Ȃ̂ł����ɒ��ڋL�q)
	template<typename T, typename... Args>
	T* AddObject(Args&&... args)
	{
		auto newObject = std::make_unique<T>(std::forward<Args>(args)...); // T�^�̃I�u�W�F�N�g���쐬
		T* objectPtr = newObject.get();
		m_Objects.push_back(std::move(newObject));
		objectPtr->Init(); // ������
		return objectPtr;
	}

	// �I�u�W�F�N�g���擾����(���e���v���[�g�֐��Ȃ̂ł����ɒ��ڋL�q)
	template<class T> std::vector<T*> GetObjects()
	{
		std::vector<T*> res;
		for (auto& o : m_Instance->m_Objects) {
			// dynamic_cast�Ō^���`�F�b�N
			if (T* derivedObj = dynamic_cast<T*>(o.get())) {
				res.emplace_back(derivedObj);
			}
		}
		return res;
	}

};
