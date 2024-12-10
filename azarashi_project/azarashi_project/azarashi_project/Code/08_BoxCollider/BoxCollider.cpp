#include "BoxCollider.h"
#include "../03_GameMainFile/Math.h"

using namespace Math;


//--------------------------------------------------------------
//傾きに合わせて長方形の角度計算関数(回転座標)
// //2024/11/14 中江
//--------------------------------------------------------------
DirectX::XMFLOAT2 BoxCollider::RotatePosition(/*矩形の中心座標*/DirectX::XMFLOAT2 point, /*矩形の角度*/float angle)
{
    DirectX::XMFLOAT2 result;
    result.x = point.x * cos(angle) - point.y * sin(angle);  //回転行列を使ってX座標を変更するよ
    result.y = point.x * sin(angle) + point.y * cos(angle);  //回転行列を使ってY座標を変更するよ 
    return result;
}

//--------------------------------------------------------------
//四角と円の当たり判定関数
//2024/11/14 中江
//--------------------------------------------------------------
bool BoxCollider::CheckCollision_Box_Circle(Object* m_GamePlayer,Object* p_block)
{
    const float angle = p_block->GetAngle() * ConvertDegreeToRadian();   //角度をラジアンに変換

    DirectX::XMFLOAT3 circlepos = m_GamePlayer->GetPos();   //ポインターを使ってcircleの座標取得
    DirectX::XMFLOAT3 circlesize =m_GamePlayer->GetSize();  //ポインターを使ってcircleのサイズ取得

    //矩形の幅と高さを半分にしておくことで座標計算が簡単になる
    DirectX::XMFLOAT2 halfsize = { p_block->GetSize().x / 2, p_block->GetSize().y / 2 };

    //幅の半分と高さの半分の数値を使って長方形の頂点の座標を計算する(o^―^o)
    hitcorners[0] = { -halfsize.x , -halfsize.y };      //左下
    hitcorners[1] = {  halfsize.x , -halfsize.y };      //右下
    hitcorners[2] = {  halfsize.x ,  halfsize.y };      //右上
    hitcorners[3] = { -halfsize.x ,  halfsize.y };      //左上

    //回転後、平行移動後の座標に変換(四つ角すべて)
    for (int i = 0; i < 4; i++) {
        hitcorners[i] = RotatePosition(hitcorners[i], angle);//長方形の各角を回転させる
        hitcorners[i].x += p_block->GetPos().x ;//変換した矩形のXに矩形の中心座標Xを足す
        hitcorners[i].y += p_block->GetPos().y ;//変換した矩形のYに矩形の中心座標Yを足す
       
    }

     // 各辺と円との距離を判定
    for (int i = 0; i < 4; i++)
    {
        DirectX::XMFLOAT2 p1 = hitcorners[i];
        DirectX::XMFLOAT2 p2 = hitcorners[(i + 1) % 4];

        // 辺の方向ベクトル
        DirectX::XMFLOAT2 edge = { p2.x - p1.x, p2.y - p1.y };                  //角から角のベクトルを図るよ
        DirectX::XMFLOAT2 toCircle = { circlepos.x - p1.x, circlepos.y - p1.y };//点から角のベクトルを図るよ

        float t = fmaxf(0 , fminf(1, (toCircle.x * edge.x + toCircle.y * edge.y) / (edge.x * edge.x + edge.y * edge.y)));
        DirectX::XMFLOAT2 closestPoint = { p1.x + t * edge.x, p1.y + t * edge.y };

        // 最近接点と円の中心の距離を計算
        float distanceSquared = (closestPoint.x - circlepos.x) * (closestPoint.x - circlepos.x) +
                                (closestPoint.y - circlepos.y) * (closestPoint.y - circlepos.y);
        // 距離が半径以下なら当たりと判定
        if (distanceSquared <= circlesize.y / 2 * circlesize.y / 2)
        {
          return true;
        }
    }

    return false;
};

//--------------------------------------------------------------
//四角と四角の当たり判定関数
//2024/12/03 中江
//--------------------------------------------------------------
bool BoxCollider::CheckCollision_Box_Box(Object* m_GamePlayer, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height)
{
    return false;
}

//--------------------------------------------------------------
//衝突判定を取る範囲にそのオブジェクトあるかどうかを調べる関数
//2024/12/7 中江 (すこし挙動がおかしいのでまた改良版を載せる)
//--------------------------------------------------------------
bool BoxCollider::IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height)
{
    // 矩形の中心から円の中心までの距離を計算 
    float distancex = range_x + wihtd / 2;
    float distancey = range_y + height / 2;
    //float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    // 距離が指定された範囲内であればtrueを返す  
    DirectX::XMFLOAT3 circlesize = { 50,50,0 };
    //ObjectのX座標が範囲に入っているなら
    if ((distancex + wihtd) * -1 <= circleposx && circleposx <= (distancex + wihtd)){
        //ObjectのY座標が範囲に入っているなら
        if ((distancey + height) * -1 <= circleposy && circleposy <= (distancey + wihtd)){
            return true;
        }
        else{
            return false;
        }
    }
    else{ 
        return false;
    }

}


