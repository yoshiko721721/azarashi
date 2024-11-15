#pragma once




#include<memory>
#include<mutex>
template <typename T>
class Singleton
{
private:
	static std::unique_ptr<T> instance;	//�V���O���g���C���X�^���X
	static std::once_flag     initFlag;	//�������t���O
protected:
	Singleton() {};  //�R���X�g���N�^��ی삵�Ă���O������̐����h�~
	~Singleton() {}; //�f�X�g���N�^



public:
	//�V���O���g���C���X�^���X���擾���郁�\�b�h
	static T& GetInstance() {
		std::call_once(initFlag, []() {
			instance.reset(new T());
		});
		return *instance;
	}

	//�R�s�[�R���X�g���N�^�Ƒ�����Z�q���폜���ĕ����h�~
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton) = delete;

};

//�ÓI�����o�̒�`
template<typename T> std::unique_ptr<T> Singleton<T>::instance;
template<typename T> std::once_flag     Singleton<T>::initFlag;
