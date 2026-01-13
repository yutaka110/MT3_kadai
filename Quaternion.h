#pragma once
#include <cmath>

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
