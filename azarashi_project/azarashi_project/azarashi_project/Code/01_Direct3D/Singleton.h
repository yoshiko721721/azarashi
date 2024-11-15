#pragma once




#include<memory>
#include<mutex>
template <typename T>
class Singleton
{
private:
	static std::unique_ptr<T> instance;	//シングルトンインスタンス
	static std::once_flag     initFlag;	//初期化フラグ
protected:
	Singleton() {};  //コンストラクタを保護してから外部からの生成防止
	~Singleton() {}; //デストラクタ



public:
	//シングルトンインスタンスを取得するメソッド
	static T& GetInstance() {
		std::call_once(initFlag, []() {
			instance.reset(new T());
		});
		return *instance;
	}

	//コピーコンストラクタと代入演算子を削除して複製防止
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton) = delete;

};

//静的メンバの定義
template<typename T> std::unique_ptr<T> Singleton<T>::instance;
template<typename T> std::once_flag     Singleton<T>::initFlag;
