#pragma once
#include"matrix4x4.h"
struct Pendulum {

    //アンカーポイント。固定された端の位置
    Vector3 anchor;       

    //紐の長さ
    float length;          

    //現在の角度
    float angle;         

    //角速度ω
    float angularVelocity;        

    //角加速度
    float angularAcceleration;    
};
