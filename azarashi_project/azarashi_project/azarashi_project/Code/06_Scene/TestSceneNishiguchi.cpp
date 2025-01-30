#include"TestSceneNishiguchi.h"
#include "../07_Camera/Camera.h"

TestSceneNishiguchi::TestSceneNishiguchi(std::vector<ID3D11ShaderResourceView*>& textures) :textures(textures)// , moveGameBlock(2.0f) // ���������X�g���g�p���ă����o�ϐ���������
{


}

void TestSceneNishiguchi::Init()
{	
	//testFloor.Init();
	//testWall.Init();
	//std::vector<ID3D11ShaderResourceView*> textures(BlockType_MAX); // �x�N�^�[�������� 
    //SVMapLoader csvMapLoader(textures); // textures �x�N�^�[��n���ď����� 
	m_MySceneObjects.emplace_back(Application::GetInstance()->AddObject<GameBackGround>());//�n�`
	bool Fopen = csvMapLoader.FileOpen(fileName);
	csvMapLoader.CountRowsAndColumns();
	csvMapLoader.FileClose();

	csvMapLoader.LoadTextures(); //textures�x�N�^�[��n�����ɌĂяo��
	p_Player = csvMapLoader.AddObject(&m_MySceneObjects);
	b_Block = Application::GetInstance()->GetObjects<GameBlock>();
	for (auto block : b_Block) {
		block->SetPos(1000,0,0);
		block[0].SetPos(0, -400, 0);
		block[0].SetAngle(0);

	}

	//csvMapLoader.PrintValueAt(3, 6);
	Camera::Lock(p_Player);
}

void TestSceneNishiguchi::Update()
{
	SDL_Event& e = Controller::Input::e;
	Controller::Input::e = e; // �C�x���g��Controller::Input::e�ɐݒ� 
	//testWall.Update();
	//testFloor.Update();
	for (auto& o : m_MySceneObjects)
	{
		o->Update(); // �e�I�u�W�F�N�g�̕`�惁�\�b�h���Ăяo
	}

	//p_Player->Update()
 	//DirectX::XMFLOAT3 pos = Player.GetPos();
	/*for (auto& o : m_MySceneObjects)
	{
		o->Update(); // �e�I�u�W�F�N�g�̕`�惁�\�b�h���Ăяo
	}*/
	if (e.type == SDL_CONTROLLERBUTTONDOWN)
	{	
		if (e.cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			std::cout << "X�{�^����������܂����I" << std::endl;
			Application::GetInstance()->ChangeScene(GAMESCENE);
			return;
		}
	}
}


void TestSceneNishiguchi::Draw()
{
	//testFloor.Draw();
	//testWall.Draw();
	for (auto& o : m_MySceneObjects)
	{
		o->Draw(); // �e�I�u�W�F�N�g�̕`�惁�\�b�h���Ăяo
	}
	/*if (pause.isPaused() == true)
	{
		pauseText.Draw();
	}*/

	//timer.Draw();*/
}

void TestSceneNishiguchi::Uninit()
{
	testFloor.Uninit();
	testWall.Uninit();
	//pauseText.Uninit();
	// ���̃V�[���̃I�u�W�F�N�g���폜���� 
	for (auto& o : m_MySceneObjects)
	{
		Application::GetInstance()->DeleteObject(o.get()); // .get()��ǉ�
	}
}

void TestSceneNishiguchi::SetPlayer()
{

}

GamePointer* TestSceneNishiguchi::GetPlayer()
{
	return p_Player;
}