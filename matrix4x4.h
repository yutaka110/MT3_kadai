#pragma once
struct Matrix4x4
{
	float m[4][4];
};


Matrix4x4 Add(Matrix4x4 m1, Matrix4x4 m2);
Matrix4x4 Subtract(Matrix4x4 m1, Matrix4x4 m2);
Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);
Matrix4x4 Inverse(Matrix4x4& m);
Matrix4x4 Transpose(Matrix4x4& m);
Matrix4x4 MakeIdentit4x4();
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix);