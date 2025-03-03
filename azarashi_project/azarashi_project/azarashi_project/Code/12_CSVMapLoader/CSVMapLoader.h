//------------------------------------------------------------------------------------------------
// CSVMapLoaderクラス
// エクセルで作ったCSVファイルのマップを読み込み、テクスチャを設定していく処理をまとめています
// 2024/12/18 中江文瞳
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
#include "../03_GameMainFile/Game/Gimmick/Wall.h"
#include "../03_GameMainFile/Game/Gimmick/Floor.h"
#include "../03_GameMainFile/Game/GameBlock.h"
#include "../01_Direct3D/direct3d.h"
#include "../01_Direct3D/Object.h"
#include "../05_WICTextureLoader/WICTextureLoader.h"
#include "../03_GameMainFile/Game/GameBlock.h"
#include "../03_GameMainFile/Game/MoveGameBlock.h"
#include"../03_GameMainFile/Game/Gimmick/Snowman.h"
#include "../03_GameMainFile/Test/TestWall.h"
#include "../03_GameMainFile/Test/Testfloor.h"
#include "../03_GameMainFile/Game/BreakBlock.h"
#include "../03_GameMainFile/Game/Gimmick/GameBlock_stop.h"
#include "../03_GameMainFile/Game/Goal.h"
//#include "../03_GameMainFile/Test/TestPointer.h"

const int BLOCKSIZE = 128;

enum BlockType//１
{ 
    NULLSPACE,
    FLOOR ,      //床
    WALL,       //壁
    PLAYER,     //プレイヤー(アザラシ)
    GOAL,
    INCLINED_PLATFORM = 11,  //傾く足場
    FLAT_PLATFORM,           //傾かない床
    BREAK_PLATFORM,          //崩れる床
    HEAYVMOVING_PLATFORM,    //動く床(重め)
    LIGHTMOVING_PLATFORM,    //動く床(軽め)
    OBSTACLE_ITEM = 21,           //お邪魔アイテム
    ROUND_ROCK,              //丸い岩
    SQUARE_ROCK,             //四角い岩
    BlockType_MAX //配列の最大値
};

class CSVMapLoader 
{
public:
    CSVMapLoader() : textures(BlockType_MAX, nullptr) , FloorBlockTextures(15, nullptr), WallBlockTextures(30, nullptr), 
        inclined_PlatformTextures(6, nullptr), Flat_PlatformTextures(6, nullptr), Break_PlatformTextures(6, nullptr) {} // コンストラクタで初期化
    ~CSVMapLoader(); bool FileOpen(std::string fileName); //ファイル開く 
    void CalculateStageCenter();
    void CountRowsAndColumns(); //行数列数数える 
    void SetStageWidth();
    void SetStageHeight();
    GamePointer* AddObject(std::vector<std::unique_ptr<Object>>* m_MySceneObjects);
    void FileClose(); //ファイル閉じる 
    
    ID3D11ShaderResourceView* LoadTexture(const wchar_t* filename); 
    void LoadTextures(); 
    std::ifstream file; 
    std::vector<std::vector<int>> data; //データを格納する二次元配列 
    std::vector<ID3D11ShaderResourceView*> textures; // テクスチャ情報を格納するベクター
    std::vector<ID3D11ShaderResourceView*> FloorBlockTextures; // 床情報を格納するベクター
    std::vector<ID3D11ShaderResourceView*> WallBlockTextures; // 壁情報を格納するベクター
    std::vector<ID3D11ShaderResourceView*> inclined_PlatformTextures; // 傾く床
    std::vector<ID3D11ShaderResourceView*> Flat_PlatformTextures; // 傾く床
    std::vector<ID3D11ShaderResourceView*> Break_PlatformTextures; // 傾く床
    
    // 必要なサイズを指定して初期化 
    ID3D11ShaderResourceView* m_pTextureView; //textureの保存場所 

    std::string line; //文字列保存場所 
private:

    int rowCount = 0; //行列 
    int colCount = 0; //列数

    int stagewide;
    int stagehigt;

    int startX;
    int startY;
};











