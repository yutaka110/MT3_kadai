#pragma once
#include <cmath>
#include "Matrix4x4.h"   // 同上
// =====================================
// Quaternion
// (x,y,z) = ベクトル部, w = スカラー部
// =====================================
struct Quaternion {
    float x, y, z, w;
};

Quaternion MultiplyQuaternion(const Quaternion& lhs, const Quaternion& rhs);
Quaternion IdentityQuaternion();
Quaternion ConjugateQuaternion(const Quaternion& q);
float NormQuaternion(const Quaternion& q);
Quaternion NormalizeQuaternion(const Quaternion& q);
Quaternion InverseQuaternion(const Quaternion& q);
// 任意軸回転を表すQuaternionの生成
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

// ベクトルをQuaternionで回転させた結果のベクトルを求める
Vector3 RotateVector(const Vector3& v, const Quaternion& q);

// Quaternionから回転行列を求める
Matrix4x4 MakeRotateMatrix(const Quaternion& q);
