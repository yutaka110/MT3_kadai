#pragma once
struct Matrix4x4
{
	float m[4][4];
};

struct Vector3
{
	float x;
	float y;
	float z;
};


Matrix4x4 Add(Matrix4x4 m1, Matrix4x4 m2);
Matrix4x4 Subtract(Matrix4x4 m1, Matrix4x4 m2);
Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);
Matrix4x4 Inverse(Matrix4x4& m);
Matrix4x4 Transpose(Matrix4x4& m);
Matrix4x4 MakeIdentit4x4();
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
Matrix4x4 MakeRoateXMatrix(float radian);
Matrix4x4 MakeRoateYMatrix(float radian);
Matrix4x4 MakeRoateZMatrix(float radian);
void VectorScreenPrintf(int x, int y, const Vector3 vector, const char* label);
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix);