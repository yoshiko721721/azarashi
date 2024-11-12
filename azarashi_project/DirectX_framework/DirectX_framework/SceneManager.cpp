#include "SceneManager.h"

std::unique_ptr<Scene>
SceneManager::currentScene = nullptr;

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
    if (currentScene)
    {
        currentScene->Uninit();//�ύX�O�Ɍ��݂̃V�[����Uninit���s��
    }

    currentScene = std::move(newScene); //�I�u�W�F�N�g�̏��L�����ړ����邽�߂̊֐�
                                        //newScene�̏��L����currentScene�Ɉڂ�
    currentScene->Init();               //���݂̃V�[���̊J�n�̏����������

}

void SceneManager::Update()
{
    if (currentScene)//�����ƍ��̃V�[���̃f�[�^�������Ă���Ȃ�
    {
        currentScene->Update();//currentScene���Q�Ƃ���Update����
    }
}

void SceneManager::Draw()
{
    if (currentScene)//�����ƍ��̃V�[���̃f�[�^�������Ă���Ȃ�
    {
        currentScene->Draw();//currentScene���Q�Ƃ���Draw����
    }
}

void SceneManager::Uninit()
{
    if (currentScene)//�����ƍ��̃V�[���̃f�[�^�������Ă���Ȃ�
    {
        currentScene->Uninit();//currentScene���Q�Ƃ���Uninit����
    }
}
