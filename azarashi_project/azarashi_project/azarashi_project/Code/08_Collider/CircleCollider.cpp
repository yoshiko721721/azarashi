#include "CircleCollider.h"
#include <algorithm>

// スコープを付けてhitcorners を定義 
DirectX::XMFLOAT2 CircleCollider::hitcorners[4];

//--------------------------------------------------------------
//傾きに合わせて長方形の角度計算関数(回転座標)
// //2024/11/14 中江
//--------------------------------------------------------------
DirectX::XMFLOAT2 CircleCollider::RotatePosition(/*矩形の中心座標*/DirectX::XMFLOAT2 point, /*矩形の角度*/float angle)
{
    DirectX::XMFLOAT2 result;
    result.x = point.x * cos(angle) - point.y * sin(angle);//回転行列を使ってX座標を変更するよ
    result.y = point.x * sin(angle) + point.y * cos(angle);//回転行列を使ってY座標を変更するよ 
    return result;
}

// ベクトルの内積を計算 
float CircleCollider::dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

//--------------------------------------------------------------
//四角と円の当たり判定関数
//2024/11/14 中江
//--------------------------------------------------------------
ContactPointVector CircleCollider::ColliderWithBox(Object* p_Box, Object* p_Circle)
{
    float angle = p_Box->GetAngle();     //四角の角度を取得
    angle = angle * (M_PI / 180.0);      //四角の角度をラジアンに変換

    DirectX::XMFLOAT3 boxpos = p_Box->GetPos();   //ポインターを使ってcircleの座標取得
    //DirectX::XMFLOAT3 boxpos2 = { boxpos.x,boxpos.y };
    DirectX::XMFLOAT3 boxsize = p_Box->GetSize();  //ポインターを使ってcircleのサイズ取得

    DirectX::XMFLOAT3 circlepos = p_Circle->GetPos();   //ポインターを使ってcircleの座標取得
    DirectX::XMFLOAT3 circlesize = p_Circle->GetSize();  //ポインターを使ってcircleのサイズ取得

    //矩形の幅と高さを半分にしておくことで座標計算が簡単になる
    DirectX::XMFLOAT2 halfsize = { boxsize.x / 2 , boxsize.y / 2 };//OK

    //幅の半分と高さの半分の数値を使って長方形の頂点の座標を計算する(o^―^o)
    hitcorners[0] = { -halfsize.x , -halfsize.y };
    hitcorners[1] = {  halfsize.x , -halfsize.y };
    hitcorners[2] = {  halfsize.x ,  halfsize.y };
    hitcorners[3] = { -halfsize.x ,  halfsize.y };//OK

    //回転後、平行移動後の座標に変換(四つ角すべて)
    for (int i = 0; i < 4; i++) {
        hitcorners[i] = RotatePosition(hitcorners[i], angle);//長方形の各角を回転させる
        hitcorners[i].x += boxpos.x;//変換した矩形のXに矩形の中心座標Xを足す
        hitcorners[i].y += boxpos.y;//変換した矩形のYに矩形の中心座標Yを足す

    }//OK

     // 各辺と円との距離を判定
    for (int i = 0; i < 4; i++)
    {
        DirectX::XMFLOAT2 p1 = hitcorners[i];
        DirectX::XMFLOAT2 p2 = hitcorners[(i + 1) % 4];

        // 辺の方向ベクトル
        DirectX::XMFLOAT2 edge = { p2.x - p1.x, p2.y - p1.y };//角から角のベクトルを図るよ
        DirectX::XMFLOAT2 toCircle = { circlepos.x - p1.x, circlepos.y - p1.y };//点から角のベクトルを図るよ

        float t = fmax(0, fmin(1, (toCircle.x * edge.x + toCircle.y * edge.y) / (edge.x * edge.x + edge.y * edge.y)));
        DirectX::XMFLOAT2 closestPoint = { p1.x + t * edge.x, p1.y + t * edge.y }; //返す値

        // 最近接点と円の中心の距離を計算
        float distanceSquared = (closestPoint.x - circlepos.x) * (closestPoint.x - circlepos.x) + (closestPoint.y - circlepos.y) * (closestPoint.y - circlepos.y);//返す値

        // 距離が半径以下なら当たりと判定
        if (distanceSquared <= (circlesize.y / 2) * (circlesize.y / 2))
        {
            DirectX::XMFLOAT2 vectorToCenter = { closestPoint.x - circlepos.x , closestPoint.y - circlepos.y };
            float length = sqrt(vectorToCenter.x * vectorToCenter.x + vectorToCenter.y * vectorToCenter.y);
            DirectX::XMFLOAT2 normalizedVector = { vectorToCenter.x / length, vectorToCenter.y / length };
            //closscircle = closestPoint;
            //distancesquared = distanceSquared;

            return { true, closestPoint ,normalizedVector };
        }
    }

    return { false };
};
//--------------------------------------------------------------
//四角と四角の当たり判定関数
//2024/12/03 中江
//--------------------------------------------------------------
bool CircleCollider::ColliderWithCircle(Object* p_Circle1, Object* p_Circle2)
{
    DirectX::XMFLOAT3 circlepos1 = p_Circle1->GetPos();
    DirectX::XMFLOAT3 circlesize1 = p_Circle1->GetSize();  //ポインターを使ってcircleのサイズ取得

    DirectX::XMFLOAT3 circlepos2 = p_Circle2->GetPos();
    DirectX::XMFLOAT3 circlesize2 = p_Circle2->GetSize();  //ポインターを使ってcircleのサイズ取得

    float radius1 = circlesize1.y / 2;
    float radius2 = circlesize2.y / 2;

    float a = circlepos1.x - circlepos2.x;
    float b = circlepos1.y - circlepos2.y;
    float c = sqrt(a * a + b * b);

    if (c <= radius1 + radius2)
    {
        return true;
    }
    else
    { 
        return false;
    }
}
//--------------------------------------------------------------
//範囲内にcircleがなにかあるかどうかを調べる関数
//2024/11/23 中江
//--------------------------------------------------------------
/* bool CircleCollider::IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height)
{
   // 矩形の中心から円の中心までの距離を計算 
    float distancex = range_x + wihtd / 2;
    float distancey = range_y + height / 2;
    //float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    // 距離が指定された範囲内であればtrueを返す  
    DirectX::XMFLOAT3 circlesize = { 50,50,0 };
    //ObjectのX座標が範囲に入っているなら
    if ((distancex + wihtd) * -1 <= circleposx && circleposx <= (distancex + wihtd)) {
        //ObjectのY座標が範囲に入っているなら
        if ((distancey + height) * -1 <= circleposy && circleposy <= (distancey + wihtd)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

}*/


