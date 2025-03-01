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


//--------------------------------------------------------------
//円と四角の当たり判定関数
//2024/12/11 中江
//--------------------------------------------------------------

ContactPointVector BoxCollider::ColliderWithCircle(Object* p_Circle, Object* p_Box)
{
    TransForm box;
    TransForm circle;

    box.TransFormInitialize(*p_Box);
    circle.TransFormInitialize(*p_Circle);

    DirectX::XMFLOAT2 normalizedVector = { 0.0f,0.0f };
    DirectX::XMFLOAT2 closestPoint     = { 0.0f,0.0f };

    // 各辺と円との距離を判定
    for (int i = 0; i < 4; i++)
    {
        DirectX::XMFLOAT2 p1 = box.vertex[i];
        DirectX::XMFLOAT2 p2 = box.vertex[(i + 1) % 4];

        // 辺の方向ベクトル
        DirectX::XMFLOAT2 edge = { p2.x - p1.x, p2.y - p1.y };//角から角のベクトルを図るよ
        DirectX::XMFLOAT2 toCircle = { circle.position.x - p1.x, circle.position.y - p1.y };//点から角のベクトルを図るよ

        float t = fmax(0, fmin(1, (toCircle.x * edge.x + toCircle.y * edge.y) / (edge.x * edge.x + edge.y * edge.y)));
        closestPoint = { p1.x + t * edge.x, p1.y + t * edge.y }; //返す値

        // 最近接点と円の中心の距離を計算
        float distanceSquared = (closestPoint.x - circle.position.x) * (closestPoint.x - circle.position.x) + (closestPoint.y - circle.position.y) * (closestPoint.y - circle.position.y);//返す値
        float radius = circle.halfSize.y;
        if (distanceSquared <= radius * radius)
        {
            float clossPointNum = Math::CalcSquareRoot(closestPoint.x, closestPoint.y);
            for (int j = 0; j < 4; ++j) {
                float hitCornerNum = Math::CalcSquareRoot(box.vertex[j].x, box.vertex[j].y);
                float distanceNum = clossPointNum - hitCornerNum;
                if (distanceNum < 0.0001 && distanceNum > -0.0001) {
                    switch (j) {
                    case 0: return{ LEFTDOWN  , (closestPoint, 0.0f) , distanceSquared };     break;
                    case 1: return{ RIGHTDOWN , (closestPoint, 0.0f) , distanceSquared };     break;
                    case 2: return{ RIGHTUP   , (closestPoint, 0.0f) , distanceSquared };     break;
                    case 3: return{ LEFTUP    , (closestPoint, 0.0f) , distanceSquared };     break;
                    }
                }
            }
            
            Radian nrmAngleR = atan2(edge.y, edge.x) + M_PI / 2.0f ;
            return { COLLISION, (closestPoint, 0.0f) ,distanceSquared };

        }
    }
    return { NO_COLLISION, (closestPoint, 0.0f) , -1 };
};
//--------------------------------------------------------------
//四角と四角の当たり判定関数
//2024/12/03 中江
//--------------------------------------------------------------
bool BoxCollider::ColliderWithBox(Object* p_Box1, Object* p_Box2)
{
    DirectX::XMFLOAT2 hitcorners2[4] = {//当たり判定をとる際の座標格納先
        { 0, 0 }, //LeftBottom
        { 0, 0 }, //RightBottom
        { 0, 0 }, //RightTop
        { 0, 0 }, //LeftTop
    };

    float angle1 = p_Box1->GetAngle();
    angle1 = angle1 * (M_PI / 180.0);   //角度をラジアンに変換
    
    DirectX::XMFLOAT3 boxpos1 = p_Box1->GetPos();   //ポインターを使ってBoxの座標取得
    DirectX::XMFLOAT3 boxsize1 = p_Box1->GetSize();  //ポインターを使ってcircleのサイズ取得

//-------------------当たり判定を持っている方の矩形計算--------------------------------
    //矩形の幅と高さを半分にしておくことで座標計算が簡単になる
    DirectX::XMFLOAT2 halfsize1 = { boxsize1.x / 2,boxsize1.y / 2 };//OK
    DirectX::XMFLOAT2 hitcorners[4];
    //幅の半分と高さの半分の数値を使って長方形の頂点の座標を計算する(o^―^o)
    hitcorners[0] = { -halfsize1.x , -halfsize1.y };
    hitcorners[1] = {  halfsize1.x , -halfsize1.y };
    hitcorners[2] = {  halfsize1.x ,  halfsize1.y };
    hitcorners[3] = { -halfsize1.x ,  halfsize1.y };//OK

    //回転後、平行移動後の座標に変換(四つ角すべて)
    for (int i = 0; i < 4; i++) {
        hitcorners[i] = RotatePosition(hitcorners[i], angle1);//長方形の各角を回転させる
        hitcorners[i].x += boxpos1.x;//変換した矩形のXに矩形の中心座標Xを足す
        hitcorners[i].y += boxpos1.y;//変換した矩形のYに矩形の中心座標Yを足す

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
    float angle2 = p_Box2->GetAngle();
    angle2 = angle2 * (M_PI / 180.0);

    DirectX::XMFLOAT3 boxpos2 = p_Box2->GetPos();   //ポインターを使ってBoxの座標取得
    DirectX::XMFLOAT3 boxsize2 = p_Box2->GetSize();  //ポインターを使ってcircleのサイズ取得

     //矩形の幅と高さを半分にしておくことで座標計算が簡単になる
    DirectX::XMFLOAT2 halfsize2 = { boxsize2.x / 2 , boxsize2.y / 2};//OK

     //幅の半分と高さの半分の数値を使って長方形の頂点の座標を計算する(o^―^o)
    hitcorners2[0] = { -halfsize2.x , -halfsize2.y };
    hitcorners2[1] = {  halfsize2.x , -halfsize2.y };
    hitcorners2[2] = {  halfsize2.x ,  halfsize2.y };
    hitcorners2[3] = { -halfsize2.x ,  halfsize2.y };//OK

    //回転後、平行移動後の座標に変換(四つ角すべて)
    for (int i = 0; i < 4; i++) {
        hitcorners2[i] = RotatePosition(hitcorners2[i], angle1);//長方形の各角を回転させる
        hitcorners2[i].x += boxpos2.x;//変換した矩形のXに矩形の中心座標Xを足す
        hitcorners2[i].y += boxpos2.y;//変換した矩形のYに矩形の中心座標Yを足す

    }//OK
 //----------------------------------------------------------------------------------------
    DirectX::XMFLOAT2 relative_position;
    DirectX::XMFLOAT2 transform_pos;

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
//bool BoxCollider::IsColliderInRange(float circleposx, float circleposy, float Scaffoldposx, float Scaffoldposy, float wihtd, float height){}



