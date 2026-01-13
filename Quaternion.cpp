#include "Quaternion.h"

Quaternion IdentityQuaternion() {
    return Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
}

Quaternion ConjugateQuaternion(const Quaternion& q) {
    return Quaternion{ -q.x, -q.y, -q.z, q.w };
}

float NormQuaternion(const Quaternion& q) {
    return std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

Quaternion NormalizeQuaternion(const Quaternion& q) {
    float n = NormQuaternion(q);
    if (n < 1e-6f) return IdentityQuaternion();
    float inv = 1.0f / n;
    return Quaternion{ q.x * inv, q.y * inv, q.z * inv, q.w * inv };
}

Quaternion InverseQuaternion(const Quaternion& q) {
    float n2 = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    if (n2 < 1e-6f) return IdentityQuaternion();
    Quaternion c = ConjugateQuaternion(q);
    float inv = 1.0f / n2;
    return Quaternion{ c.x * inv, c.y * inv, c.z * inv, c.w * inv };
}

Quaternion MultiplyQuaternion(const Quaternion& a, const Quaternion& b) {
    Quaternion r;
    r.x = a.w * b.x + b.w * a.x + (a.y * b.z - a.z * b.y);
    r.y = a.w * b.y + b.w * a.y + (a.z * b.x - a.x * b.z);
    r.z = a.w * b.z + b.w * a.z + (a.x * b.y - a.y * b.x);
    r.w = a.w * b.w - (a.x * b.x + a.y * b.y + a.z * b.z);
    return r;
}
