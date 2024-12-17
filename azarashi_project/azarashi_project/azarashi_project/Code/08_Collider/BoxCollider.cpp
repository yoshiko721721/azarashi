#include "BoxCollider.h"
#include <algorithm>

//--------------------------------------------------------------
//傾きに合わせて長方形の角度計算関数(回転座標)
// //2024/11/14 中江
//--------------------------------------------------------------
DirectX::XMFLOAT2 BoxCollider::RotatePosition(/*矩形の中心座標*/DirectX::XMFLOAT2 point, /*矩形の角度*/float angle)
{
    DirectX::XMFLOAT2 result;
    result.x = point.x * cos(angle) - point.y * sin(angle);//回転行列を使ってX座標を変更するよ
    result.y = point.x * sin(angle) + point.y * cos(angle);//回転行列を使ってY座標を変更するよ 
    return result;
}

// ベクトルの内積を計算 
float BoxCollider::dotProduct(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2)
{ 
    return v1.x * v2.x + v1.y * v2.y; 
}

//--------------------------------------------------------------
//円と四角の当たり判定関数
//2024/12/11 中江
//--------------------------------------------------------------

ContactPointVector BoxCollider::ColliderWithCircle(Object* m_GamePlayer, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height)
{
    angle = angle * (M_PI / 180.0);   //角度をラジアンに変換

    DirectX::XMFLOAT3 circlepos = m_GamePlayer->GetPos();   //ポインターを使ってcircleの座標取得
    DirectX::XMFLOAT2 circlepos2 = { circlepos.x,circlepos.y };
    DirectX::XMFLOAT3 circlesize =m_GamePlayer->GetSize();  //ポインターを使ってcircleのサイズ取得

    //矩形の幅と高さを半分にしておくことで座標計算が簡単になる
    DirectX::XMFLOAT2 halfsize = { wihtd / 2,height / 2 };//OK

    //幅の半分と高さの半分の数値を使って長方形の頂点の座標を計算する(o^―^o)
    hitcorners[0] = { -halfsize.x , -halfsize.y };
    hitcorners[1] = {  halfsize.x , -halfsize.y };
    hitcorners[2] = {  halfsize.x ,  halfsize.y };
    hitcorners[3] = { -halfsize.x ,  halfsize.y };//OK

    //回転後、平行移動後の座標に変換(四つ角すべて)
    for (int i = 0; i < 4; i++) {
        hitcorners[i] = RotatePosition(hitcorners[i], angle);//長方形の各角を回転させる
        hitcorners[i].x += Scaffoldposx;//変換した矩形のXに矩形の中心座標Xを足す
        hitcorners[i].y += Scaffoldposy;//変換した矩形のYに矩形の中心座標Yを足す
       
    }//OK

    DirectX::XMFLOAT2 normalizedVector = {0.0f,0.0f};
    DirectX::XMFLOAT2 closestPoint = { 0.0f,0.0f };

     // 各辺と円との距離を判定
    for(int i = 0; i < 4; i++)
    {
        DirectX::XMFLOAT2 p1 = hitcorners[i];
        DirectX::XMFLOAT2 p2 = hitcorners[(i + 1) % 4];

        // 辺の方向ベクトル
        DirectX::XMFLOAT2 edge = { p2.x - p1.x, p2.y - p1.y };//角から角のベクトルを図るよ
        DirectX::XMFLOAT2 toCircle = { circlepos.x - p1.x, circlepos.y - p1.y };//点から角のベクトルを図るよ

        float t = fmax(0, fmin(1, (toCircle.x * edge.x + toCircle.y * edge.y) / (edge.x * edge.x + edge.y * edge.y)));
        closestPoint = { p1.x + t * edge.x, p1.y + t * edge.y }; //返す値

        // 最近接点と円の中心の距離を計算
        float distanceSquared = (closestPoint.x - circlepos.x) * (closestPoint.x - circlepos.x) + (closestPoint.y - circlepos.y) * (closestPoint.y - circlepos.y);//返す値
        // 距離が半径以下なら当たりと判定
        if (distanceSquared <= circlesize.y / 2 * circlesize.y / 2)
        {
            DirectX::XMFLOAT2 vectorToCenter = { closestPoint.x - circlepos.x , closestPoint.y - circlepos.y };
            float length = sqrt(vectorToCenter.x * vectorToCenter.x + vectorToCenter.y * vectorToCenter.y); 
           normalizedVector = { vectorToCenter.x / length, vectorToCenter.y / length };
            //closscircle = closestPoint;
            //distancesquared = distanceSquared;

            return { true, closestPoint ,normalizedVector };

        }
    }
    return { false, closestPoint ,normalizedVector };
};
//--------------------------------------------------------------
//四角と四角の当たり判定関数
//2024/12/03 中江
//--------------------------------------------------------------
bool BoxCollider::ColliderWithBox(Object* m_GamePlayer, float Scaffoldposx, float Scaffoldposy, float angle, float wihtd, float height, DirectX::XMFLOAT2& touchbox)
{
    DirectX::XMFLOAT2 hitcorners2[4] = {//当たり判定をとる際の座標格納先
        { 0, 0 }, //LeftBottom
        { 0, 0 }, //RightBottom
        { 0, 0 }, //RightTop
        { 0, 0 }, //LeftTop
    };

    angle = angle * (M_PI / 180.0);   //角度をラジアンに変換
    float angle1 = m_GamePlayer->GetAngle();
    angle1 = angle1 * (M_PI / 180.0);

    DirectX::XMFLOAT3 boxpos = m_GamePlayer->GetPos();   //ポインターを使ってBoxの座標取得
    DirectX::XMFLOAT2 boxpos2 = { boxpos.x,boxpos.y };
    DirectX::XMFLOAT3 boxsize = m_GamePlayer->GetSize();  //ポインターを使ってcircleのサイズ取得

//-------------------当たり判定を持っている方の矩形計算--------------------------------
    //矩形の幅と高さを半分にしておくことで座標計算が簡単になる
    DirectX::XMFLOAT2 halfsize1 = { wihtd / 2,height / 2 };//OK

    //幅の半分と高さの半分の数値を使って長方形の頂点の座標を計算する(o^―^o)
    hitcorners[0] = { -halfsize1.x , -halfsize1.y };
    hitcorners[1] = {  halfsize1.x , -halfsize1.y };
    hitcorners[2] = {  halfsize1.x ,  halfsize1.y };
    hitcorners[3] = { -halfsize1.x ,  halfsize1.y };//OK

    //回転後、平行移動後の座標に変換(四つ角すべて)
    for (int i = 0; i < 4; i++) {
        hitcorners[i] = RotatePosition(hitcorners[i], angle);//長方形の各角を回転させる
        hitcorners[i].x += Scaffoldposx;//変換した矩形のXに矩形の中心座標Xを足す
        hitcorners[i].y += Scaffoldposy;//変換した矩形のYに矩形の中心座標Yを足す

    }//OK

    DirectX::XMFLOAT2 edge[4];//ベクトルを保存する配列です

    for (int i = 0; i < 4; i++)//全ての辺のベクトルを計算するfor文
    {
        DirectX::XMFLOAT2 p1 = hitcorners[i];
        DirectX::XMFLOAT2 p2 = hitcorners[(i + 1) % 4];
        // 辺の方向ベクトル
        edge[i] = { p2.x - p1.x, p2.y - p1.y };//角から角のベクトルを図るよ
    }

//----------------------------------------------------------------------------------------

     //矩形の幅と高さを半分にしておくことで座標計算が簡単になる
    DirectX::XMFLOAT2 halfsize2 = { boxsize.x / 2 , boxsize.y / 2};//OK

     //幅の半分と高さの半分の数値を使って長方形の頂点の座標を計算する(o^―^o)
    hitcorners2[0] = { -halfsize2.x , -halfsize2.y };
    hitcorners2[1] = {  halfsize2.x , -halfsize2.y };
    hitcorners2[2] = {  halfsize2.x ,  halfsize2.y };
    hitcorners2[3] = { -halfsize2.x ,  halfsize2.y };//OK

    //回転後、平行移動後の座標に変換(四つ角すべて)
    for (int i = 0; i < 4; i++) {
        hitcorners2[i] = RotatePosition(hitcorners2[i], angle1);//長方形の各角を回転させる
        hitcorners2[i].x += boxpos.x;//変換した矩形のXに矩形の中心座標Xを足す
        hitcorners2[i].y += boxpos.y;//変換した矩形のYに矩形の中心座標Yを足す

    }//OK
 //----------------------------------------------------------------------------------------
    DirectX::XMFLOAT2 relative_position;
    DirectX::XMFLOAT2 transform_pos;
    /*for (int i = 0; i < 4; i++)
    {
        //角の相対座標を作り出す
        relative_position = { hitcorners2[i].x - Scaffoldposx , hitcorners2[i].y - Scaffoldposy };

        //相対座標に対して矩形の回転を打ち消す逆行列を掛ける
        transform_pos = { cos(angle) * relative_position.x + sin(angle) * relative_position.y ,-sin(angle) * relative_position.x + cos(angle) * relative_position.y };

         // 矩形と点の当たり判定を行う
        if (-halfsize1.x <= transform_pos.x && halfsize1.x >= transform_pos.x && -halfsize1.y <= transform_pos.y && halfsize1.y >= transform_pos.y)
        {
            return true;
        }
    }*/

     for(int i = 0;i < 4;i++)
     {
        //角の相対座標を作り出す
         float slope1 = (hitcorners[(i + 1) % 4].y - hitcorners[i].y) / (hitcorners[(i + 1) % 4].x - (hitcorners[i].x + 0.0001));

        for (int j = 0; j < 4; j++)
        {
            float slope2 = (hitcorners2[(j + 1) % 4].y - hitcorners2[j].y) / (hitcorners2[(j + 1) % 4].x - (hitcorners2[j].x + 0.0001));
            if (slope1 != slope2)
            {
                DirectX::XMFLOAT2 crossPoint;
                crossPoint.x = (hitcorners2[j].y - hitcorners[i].y + slope1 * hitcorners[i].x - slope2 * hitcorners2[j].x) / (slope1 - slope2);
                crossPoint.y = slope1 * (crossPoint.x - hitcorners[i].x) + hitcorners[i].y;

                float r0 = (crossPoint.x -  hitcorners[i].x) / (hitcorners[(i + 1) % 4].x - hitcorners[i].x);//線分の範囲を決める(足場側
                float r1 = (crossPoint.x - hitcorners2[j].x) / (hitcorners2[(j + 1) % 4].x - hitcorners2[j].x - 0.0001);//線分の範囲を決める(持ってきたBox側)

                if (r0 <= 1 && r0 >= 0 && r1 <= 1 && r1 >= 0)
                {
                    return true;
                }
            }
        }
        
     }

    return false;
}
//--------------------------------------------------------------
//範囲内にcircleがなにかあるかどうかを調べる関数
//2024/11/23 中江
//--------------------------------------------------------------
bool BoxCollider::IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height)
{
    // 矩形の中心から円の中心までの距離を計算 
    float distancex = range_x + wihtd  / 2;
    float distancey = range_y + height / 2;
    //float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
    // 距離が指定された範囲内であればtrueを返す  
    //ObjectのX座標が範囲に入っているなら
    if ((distancex + wihtd) * -1 <= circleposx && circleposx <= (distancex + wihtd))
    {
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

//進捗メモ 2024/11/25 中江
// やばい所
//・足場の端っこ(円の真ん中より外側)だけ足場に当たっている時に判定が発動しない
//・斜めにしたときにちょっと円が食い込む(一番やばいしイライラする)
//改善案
//・角の部分だけ別で当たり判定を取る
//・円の真ん中から線分飛ばしてあたってたらそこで当たっている判定にする


