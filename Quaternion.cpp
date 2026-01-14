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

static float DotQuaternion(const Quaternion& a, const Quaternion& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

static Quaternion ScaleQuaternion(const Quaternion& q, float s) {
    return Quaternion{ q.x * s, q.y * s, q.z * s, q.w * s };
}

static Quaternion AddQuaternion(const Quaternion& a, const Quaternion& b) {
    return Quaternion{ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

Quaternion Slerp(const Quaternion& q0In, const Quaternion& q1In, float t)
{
    // q0,q1 は単位Quaternion前提（課題の注意点）
    Quaternion q0 = q0In;
    Quaternion q1 = q1In;

    // 内積（cos）
    float dot = DotQuaternion(q0, q1);

    // 反対側（長い回転）を避ける：dot<0なら片方を反転
    if (dot < 0.0f) {
        q1 = ScaleQuaternion(q1, -1.0f);
        dot = -dot;
    }

    // 数値誤差で1を超えるのを防ぐ
    if (dot > 1.0f) dot = 1.0f;

    // ほぼ同じ向きなら Lerp で近似（sin(theta)が0に近くなるのを回避）
    const float DOT_THRESHOLD = 0.9995f;
    if (dot > DOT_THRESHOLD) {
        // lerp: (1-t)q0 + t q1
        Quaternion r = AddQuaternion(ScaleQuaternion(q0, 1.0f - t), ScaleQuaternion(q1, t));
        // ※注意点にある通り「Slerp内で正規化は避ける」方針ならここで返す
        // ただ、ここだけは誤差が出やすいので課題的に見た目一致を優先するなら正規化しても良い。
        // 指示に合わせて「正規化しない」版にしている。
        return r;
    }

    // 角度
    float theta = acosf(dot);
    float sinTheta = sinf(theta);

    // scale0 = sin((1-t)θ)/sinθ, scale1 = sin(tθ)/sinθ
    float scale0 = sinf((1.0f - t) * theta) / sinTheta;
    float scale1 = sinf(t * theta) / sinTheta;

    Quaternion r = AddQuaternion(ScaleQuaternion(q0, scale0), ScaleQuaternion(q1, scale1));
    return r;
}
