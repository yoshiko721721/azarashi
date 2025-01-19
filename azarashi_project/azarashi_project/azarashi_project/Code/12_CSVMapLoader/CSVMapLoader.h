//------------------------------------------------------------------------------------------------
// CSVMapLoader�N���X
// �G�N�Z���ō����CSV�t�@�C���̃}�b�v��ǂݍ��݁A�e�N�X�`����ݒ肵�Ă����������܂Ƃ߂Ă��܂�
// 2024/12/18 ���]����
//-------------------------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <DirectXMath.h>
#include <vector> 
#include <d3d11.h>
#include "../03_GameMainFile/Application.h"
#include "../03_GameMainFile/Game/GameBackGround.h"
#include "../03_GameMainFile/Game/GamePointer.h"
#include "../03_GameMainFile/Test/TestWall.h"
#include "../03_GameMainFile/Test/Testfloor.h"
#include "../03_GameMainFile/Game/GameBlock.h"
#include "../01_Direct3D/direct3d.h"
#include "../01_Direct3D/Object.h"
#include "../05_WICTextureLoader/WICTextureLoader.h"

enum BlockSize
{


};

enum BlockType//�P
{ 
    NULLSPACE,
    FLOOR ,      //��
    WALL,       //��
    PLAYER,     //�v���C���[(�A�U���V)
    GOAL,
    INCLINED_PLATFORM = 11,  //�X������
    FLAT_PLATFORM,           //�X���Ȃ���
    BREAK_PLATFORM,          //����鏰
    HEAYVMOVING_PLATFORM,    //������(�d��)
    LIGHTMOVING_PLATFORMb,    //������(�y��)
    OBSTACLE_ITEM = 21,           //���ז��A�C�e��
    ROUND_ROCK,              //�ۂ���
    SQUARE_ROCK,
    BlockType_MAX //�z��̍ő�l
};

class CSVMapLoader 
{
public:
    CSVMapLoader() : textures(BlockType_MAX, nullptr) {} // �R���X�g���N�^�ŏ�����
    ~CSVMapLoader(); bool FileOpen(std::string fileName); //�t�@�C���J�� 
    void CountRowsAndColumns(); //�s���񐔐����� 
    int PrintValueAt(int row, int col);
    void AddObject(std::vector<std::unique_ptr<Object>>* m_MySceneObjects);
    void FileClose(); //�t�@�C������ 
    
    ID3D11ShaderResourceView* LoadTexture(const wchar_t* filename); 
    void LoadTextures(); 
    std::ifstream file; 
    std::vector<std::vector<int>> data; //�f�[�^���i�[����񎟌��z�� 
    std::vector<ID3D11ShaderResourceView*> textures; // �e�N�X�`�������i�[����x�N�^�[
    
    // �K�v�ȃT�C�Y���w�肵�ď����� 
    ID3D11ShaderResourceView* m_pTextureView; //texture�̕ۑ��ꏊ 

    std::string line; //������ۑ��ꏊ 
    int rowCount = 0; //�s�� 
    int colCount = 0; //��
};











