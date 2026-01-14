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
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
    // 軸は正規化必須
    Vector3 a = Normalize(axis);

    float half = angle * 0.5f;
    float s = sinf(half);
    float c = cosf(half);

    // q = (a * sin(θ/2), cos(θ/2))
    Quaternion q;
    q.x = a.x * s;
    q.y = a.y * s;
    q.z = a.z * s;
    q.w = c;

    // 数値誤差対策で正規化（軸が変でも安定）
    return NormalizeQuaternion(q);
}

Vector3 RotateVector(const Vector3& v, const Quaternion& q)
{
    // v' = q * (v,0) * q^{-1}
    Quaternion p{ v.x, v.y, v.z, 0.0f };

    Quaternion qi = InverseQuaternion(q);

    Quaternion t = MultiplyQuaternion(q, p);
    Quaternion r = MultiplyQuaternion(t, qi);

    return Vector3{ r.x, r.y, r.z };
}

Matrix4x4 MakeRotateMatrix(const Quaternion& qIn)
{
    // 単位Quaternion前提（念のため正規化）
    Quaternion q = NormalizeQuaternion(qIn);

    float x = q.x, y = q.y, z = q.z, w = q.w;

    Matrix4x4 m{};
    // （右手系・列ベクトル/行ベクトルで転置が必要な環境がある）
    // まずは一般的な形を入れる。もし結果が左右反転なら「転置」すれば一致する。

    m.m[0][0] = 1.0f - 2.0f * (y * y + z * z);
    m.m[0][1] = 2.0f * (x * y + z * w);
    m.m[0][2] = 2.0f * (x * z - y * w);
    m.m[0][3] = 0.0f;

    m.m[1][0] = 2.0f * (x * y - z * w);
    m.m[1][1] = 1.0f - 2.0f * (x * x + z * z);
    m.m[1][2] = 2.0f * (y * z + x * w);
    m.m[1][3] = 0.0f;

    m.m[2][0] = 2.0f * (x * z + y * w);
    m.m[2][1] = 2.0f * (y * z - x * w);
    m.m[2][2] = 1.0f - 2.0f * (x * x + y * y);
    m.m[2][3] = 0.0f;

    m.m[3][0] = 0.0f;
    m.m[3][1] = 0.0f;
    m.m[3][2] = 0.0f;
    m.m[3][3] = 1.0f;

    return m;
}