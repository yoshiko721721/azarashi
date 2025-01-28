#include "Stage1-1Scene.h" 
#include "../../03_GameMainFile/Application.h" 

StageScene::StageScene(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures)// , moveGameBlock(2.0f) // ���������X�g���g�p���ă����o�ϐ���������
{


}

void StageScene::Init()
{
	bool Fopen = csvMapLoader.FileOpen(fileName);
	csvMapLoader.CountRowsAndColumns();
	csvMapLoader.FileClose();
	csvMapLoader.LoadTextures(); //textures�x�N�^�[��n�����ɌĂяo��
	p_Player = csvMapLoader.AddObject(&m_MySceneObjects);
	backGround.Init();
	stageExplanationUI.Init();
	Camera::Lock(p_Player);
}

void StageScene::Update()//8,6
{
	if (stageExplanation)
	{
		if (Input::GetButtonTrigger(XINPUT_B))
		{
			stageExplanation = false;
			//Application::GetInstance()->ChangeScene(GAMESCENE);
			return;
		}
		return;
	}
	backGround.Update();
	// �C�x���g��Controller::Input::e�ɐݒ� 
	for (auto& o : m_MySceneObjects)
	{
		o->Update(); // �e�I�u�W�F�N�g�̕`�惁�\�b�h���Ăяo
	}

	if (Input::GetButtonTrigger(XINPUT_B))
	{
		Application::GetInstance()->ChangeScene(GAMESCENE);
		return;
	}
}

void StageScene::Draw()
{
	backGround.Draw();
	//Player.Draw();
	for (auto& o : m_MySceneObjects)
	{
		o->Draw(); // �e�I�u�W�F�N�g�̕`�惁�\�b�h���Ăяo
	}
	
	if (stageExplanation)
	{
		stageExplanationUI.Draw();
	}
}

void StageScene::Uninit()
{
	backGround.Uninit();
	stageExplanationUI.Uninit();
	//Player.Uninit();
	for (auto& o : m_MySceneObjects)
	{
		Application::GetInstance()->DeleteObject(o.get()); // .get()��ǉ�
	}
	Camera::UnLock();
}