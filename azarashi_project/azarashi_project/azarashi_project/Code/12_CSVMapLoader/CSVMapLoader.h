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
#include "../01_Direct3D/direct3d.h"
#include "../05_WICTextureLoader/WICTextureLoader.h"

enum BlockType//１
{ 
    NULLSPACE,
    PLAYER,     //プレイヤー(アザラシ)
    FLOOR,      //床
    WALL,       //壁
    INCLINED_PLATFORM,  //傾く足場
    MOVING_PLATFORM,
    BlockType_MAX //配列の最大値
};

class CSVMapLoader 
{
public:
    CSVMapLoader() : textures(BlockType_MAX, nullptr) {} // コンストラクタで初期化
    ~CSVMapLoader(); bool FileOpen(std::string fileName); //ファイル開く 
    void CountRowsAndColumns(); //行数列数数える 
    int PrintValueAt(int row, int col);
    void FileClose(); //ファイル閉じる 
    
    ID3D11ShaderResourceView* LoadTexture(const wchar_t* filename); 
    void LoadTextures(); 
    std::ifstream file; 
    std::vector<std::vector<int>> data; //データを格納する二次元配列 
    std::vector<ID3D11ShaderResourceView*> textures; // テクスチャ情報を格納するベクター
    
    // 必要なサイズを指定して初期化 
    ID3D11ShaderResourceView* m_pTextureView; //textureの保存場所 

    std::string line; //文字列保存場所 
    int rowCount = 0; //行列 
    int colCount = 0; //列数
};











