#pragma once
#include"matrix4x4.h"
struct Spring {
    // アンカー。固定された端の位置
    Vector3 anchor;
    float naturalLength;  // 自然長
    float stiffness;      // 剛性・バネ定数k
    float dampingCoefficient;   // 減衰係数
};

struct Ball {
    Vector3 position;     // ボールの位置
    Vector3 velocity;     // ボールの速度
    Vector3 acceleration; // ボールの加速度
    float mass;           // ボールの質量
    float radius;         // ボールの半径
    unsigned int color;   // ボールの色
};