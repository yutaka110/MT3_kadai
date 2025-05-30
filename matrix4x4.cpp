
#include <Novice.h>
#include "matrix4x4.h"
#include <cmath>
#include<algorithm>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include<math.h>
#define _USE_MATH_DEFINES
Matrix4x4 Add(Matrix4x4 m1, Matrix4x4 m2)
{
	Matrix4x4 result;
	result.m[0][0] = m1.m[0][0] + m2.m[0][0];   result.m[0][1] = m1.m[0][1] + m2.m[0][1];  result.m[0][2] = m1.m[0][2] + m2.m[0][2]; result.m[0][3] = m1.m[0][3] + m2.m[0][3];
	result.m[1][0] = m1.m[1][0] + m2.m[1][0]; 	result.m[1][1] = m1.m[1][1] + m2.m[1][1];  result.m[1][2] = m1.m[1][2] + m2.m[1][2]; result.m[1][3] = m1.m[1][3] + m2.m[1][3];
	result.m[2][0] = m1.m[2][0] + m2.m[2][0]; 	result.m[2][1] = m1.m[2][1] + m2.m[2][1];  result.m[2][2] = m1.m[2][2] + m2.m[2][2]; result.m[2][3] = m1.m[2][3] + m2.m[2][3];
	result.m[3][0] = m1.m[3][0] + m2.m[3][0]; 	result.m[3][1] = m1.m[3][1] + m2.m[3][1];  result.m[3][2] = m1.m[3][2] + m2.m[3][2]; result.m[3][3] = m1.m[3][3] + m2.m[3][3];
	return result;
}

Matrix4x4 Subtract(Matrix4x4 m1, Matrix4x4 m2)
{
	Matrix4x4 result;
	result.m[0][0] = m1.m[0][0] - m2.m[0][0];   result.m[0][1] = m1.m[0][1] - m2.m[0][1];  result.m[0][2] = m1.m[0][2] - m2.m[0][2]; result.m[0][3] = m1.m[0][3] - m2.m[0][3];
	result.m[1][0] = m1.m[1][0] - m2.m[1][0]; 	result.m[1][1] = m1.m[1][1] - m2.m[1][1];  result.m[1][2] = m1.m[1][2] - m2.m[1][2]; result.m[1][3] = m1.m[1][3] - m2.m[1][3];
	result.m[2][0] = m1.m[2][0] - m2.m[2][0]; 	result.m[2][1] = m1.m[2][1] - m2.m[2][1];  result.m[2][2] = m1.m[2][2] - m2.m[2][2]; result.m[2][3] = m1.m[2][3] - m2.m[2][3];
	result.m[3][0] = m1.m[3][0] - m2.m[3][0]; 	result.m[3][1] = m1.m[3][1] - m2.m[3][1];  result.m[3][2] = m1.m[3][2] - m2.m[3][2]; result.m[3][3] = m1.m[3][3] - m2.m[3][3];
	return result;
}

Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2)
{
	Matrix4x4 result;

	float a11 = m1.m[0][0]; float a12 = m1.m[0][1]; float a13 = m1.m[0][2]; float a14 = m1.m[0][3];
	float a21 = m1.m[1][0]; float a22 = m1.m[1][1]; float a23 = m1.m[1][2]; float a24 = m1.m[1][3];
	float a31 = m1.m[2][0]; float a32 = m1.m[2][1]; float a33 = m1.m[2][2]; float a34 = m1.m[2][3];
	float a41 = m1.m[3][0]; float a42 = m1.m[3][1]; float a43 = m1.m[3][2]; float a44 = m1.m[3][3];

	float b11 = m2.m[0][0]; float b12 = m2.m[0][1]; float b13 = m2.m[0][2]; float b14 = m2.m[0][3];
	float b21 = m2.m[1][0]; float b22 = m2.m[1][1]; float b23 = m2.m[1][2]; float b24 = m2.m[1][3];
	float b31 = m2.m[2][0]; float b32 = m2.m[2][1]; float b33 = m2.m[2][2]; float b34 = m2.m[2][3];
	float b41 = m2.m[3][0]; float b42 = m2.m[3][1]; float b43 = m2.m[3][2]; float b44 = m2.m[3][3];

	result.m[0][0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41; result.m[0][1] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42; result.m[0][2] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43; result.m[0][3] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;
	result.m[1][0] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41; result.m[1][1] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42; result.m[1][2] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43; result.m[1][3] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;
	result.m[2][0] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41; result.m[2][1] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42; result.m[2][2] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43; result.m[2][3] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;
	result.m[3][0] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41; result.m[3][1] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42; result.m[3][2] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43; result.m[3][3] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

	return result;
}

//Matrix4x4 Inverse(Matrix4x4& m)
//{
//	Matrix4x4 result;
//
//	float a11 = m.m[0][0]; float a21 = m.m[0][1]; float a31 = m.m[0][2]; float a41 = m.m[0][3];
//	float a12 = m.m[1][0]; float a22 = m.m[1][1]; float a32 = m.m[1][2]; float a42 = m.m[1][3];
//	float a13 = m.m[2][0]; float a23 = m.m[2][1]; float a33 = m.m[2][2]; float a43 = m.m[2][3];
//	float a14 = m.m[3][0]; float a24 = m.m[3][1]; float a34 = m.m[3][2]; float a44 = m.m[3][3];
//
//	result.m[0][0] = a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 - a24 * a33 * a42 - a23 * a32 * a44 - a22 * a34 * a43;
//	result.m[0][1] = -a12 * a33 * a44 - a13 * a34 * a42 - a14 * a32 * a43 + a14 * a33 * a42 + a13 * a32 * a44 + a12 * a34 * a43;
//	result.m[0][2] = a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 - a14 * a23 * a42 - a13 * a22 * a44 - a12 * a24 * a43;
//	result.m[0][3] = -a12 * a23 * a34 - a13 * a24 * a32 - a14 * a22 * a33 + a14 * a23 * a32 + a13 * a22 * a34 + a12 * a24 * a33;
//
//	result.m[1][0] = -a21 * a33 * a44 - a23 * a34 * a41 - a24 * a31 * a43 + a24 * a33 * a41 + a23 * a31 * a44 + a21 * a34 * a43;
//	result.m[1][1] = a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 - a14 * a33 * a41 - a13 * a31 * a44 - a11 * a34 * a43;
//	result.m[1][2] = -a11 * a23 * a44 - a13 * a24 * a41 - a14 * a21 * a43 + a14 * a23 * a41 + a13 * a21 * a44 + a11 * a24 * a43;
//	result.m[1][3] = a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 - a14 * a23 * a31 - a13 * a21 * a34 - a11 * a24 * a33;
//
//	result.m[2][0] = a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 - a24 * a32 * a41 - a22 * a31 * a44 - a21 * a34 * a42;
//	result.m[2][1] = -a11 * a32 * a44 - a12 * a34 * a41 - a14 * a31 * a42 + a14 * a32 * a41 + a12 * a31 * a44 + a11 * a34 * a42;
//	result.m[2][2] = a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 - a14 * a22 * a41 - a12 * a21 * a44 - a11 * a24 * a42;
//	result.m[2][3] = -a11 * a22 * a34 - a12 * a24 * a31 - a14 * a21 * a32 + a14 * a22 * a31 + a12 * a21 * a34 + a11 * a24 * a32;
//
//	result.m[3][0] = -a21 * a32 * a43 - a22 * a33 * a41 - a23 * a31 * a42 + a23 * a32 * a41 + a22 * a31 * a43 + a21 * a33 * a42;
//	result.m[3][1] = a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 - a13 * a32 * a41 - a12 * a31 * a43 - a11 * a33 * a42;
//	result.m[3][2] = -a11 * a22 * a43 - a12 * a23 * a41 - a13 * a21 * a42 + a13 * a22 * a41 + a12 * a21 * a43 + a11 * a23 * a42;
//	result.m[3][3] = a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a13 * a22 * a31 - a12 * a21 * a33 - a11 * a23 * a32;
//
//
//	for (int i = 0; i < 4; ++i)
//	{
//		for (int j = 0; j < 4; ++j)
//		{
//			result.m[j][i] /= (a11 * a22 * a33 * a44 + a11 * a23 * a34 * a42 + a11 * a24 * a32 * a43 - a11 * a24 * a33 * a42 - a11 * a23 * a32 * a44 - a11 * a22 * a34 * a43 - a12 * a21 * a33 * a44 - a13 * a21 * a34 * a42 - a14 * a21 * a32 * a43 + a14 * a21 * a33 * a42 + a13 * a21 * a32 * a44 + a12 * a21 * a34 * a43 +
//				a12 * a23 * a31 * a44 + a13 * a24 * a31 * a42 + a14 * a22 * a31 * a43 - a14 * a23 * a34 * a41 - a13 * a24 * a32 * a41 - a14 * a22 * a33 * a41 + a14 * a23 * a32 * a41 + a13 * a22 * a34 * a41 + a12 * a24 * a33 * a41);
//		}
//	}
//
//	return result;
//}

Matrix4x4 Inverse(Matrix4x4& m) {
	Matrix4x4 result;
	float* a = &m.m[0][0];

	float cof[16];
	float det;


	cof[0] = a[5] * a[10] * a[15] - a[5] * a[11] * a[14] - a[9] * a[6] * a[15]
		+ a[9] * a[7] * a[14] + a[13] * a[6] * a[11] - a[13] * a[7] * a[10];
	cof[1] = -a[1] * a[10] * a[15] + a[1] * a[11] * a[14] + a[9] * a[2] * a[15]
		- a[9] * a[3] * a[14] - a[13] * a[2] * a[11] + a[13] * a[3] * a[10];
	cof[2] = a[1] * a[6] * a[15] - a[1] * a[7] * a[14] - a[5] * a[2] * a[15]
		+ a[5] * a[3] * a[14] + a[13] * a[2] * a[7] - a[13] * a[3] * a[6];
	cof[3] = -a[1] * a[6] * a[11] + a[1] * a[7] * a[10] + a[5] * a[2] * a[11]
		- a[5] * a[3] * a[10] - a[9] * a[2] * a[7] + a[9] * a[3] * a[6];

	cof[4] = -a[4] * a[10] * a[15] + a[4] * a[11] * a[14] + a[8] * a[6] * a[15]
		- a[8] * a[7] * a[14] - a[12] * a[6] * a[11] + a[12] * a[7] * a[10];
	cof[5] = a[0] * a[10] * a[15] - a[0] * a[11] * a[14] - a[8] * a[2] * a[15]
		+ a[8] * a[3] * a[14] + a[12] * a[2] * a[11] - a[12] * a[3] * a[10];
	cof[6] = -a[0] * a[6] * a[15] + a[0] * a[7] * a[14] + a[4] * a[2] * a[15]
		- a[4] * a[3] * a[14] - a[12] * a[2] * a[7] + a[12] * a[3] * a[6];
	cof[7] = a[0] * a[6] * a[11] - a[0] * a[7] * a[10] - a[4] * a[2] * a[11]
		+ a[4] * a[3] * a[10] + a[8] * a[2] * a[7] - a[8] * a[3] * a[6];

	cof[8] = a[4] * a[9] * a[15] - a[4] * a[11] * a[13] - a[8] * a[5] * a[15]
		+ a[8] * a[7] * a[13] + a[12] * a[5] * a[11] - a[12] * a[7] * a[9];
	cof[9] = -a[0] * a[9] * a[15] + a[0] * a[11] * a[13] + a[8] * a[1] * a[15]
		- a[8] * a[3] * a[13] - a[12] * a[1] * a[11] + a[12] * a[3] * a[9];
	cof[10] = a[0] * a[5] * a[15] - a[0] * a[7] * a[13] - a[4] * a[1] * a[15]
		+ a[4] * a[3] * a[13] + a[12] * a[1] * a[7] - a[12] * a[3] * a[5];
	cof[11] = -a[0] * a[5] * a[11] + a[0] * a[7] * a[9] + a[4] * a[1] * a[11]
		- a[4] * a[3] * a[9] - a[8] * a[1] * a[7] + a[8] * a[3] * a[5];

	cof[12] = -a[4] * a[9] * a[14] + a[4] * a[10] * a[13] + a[8] * a[5] * a[14]
		- a[8] * a[6] * a[13] - a[12] * a[5] * a[10] + a[12] * a[6] * a[9];
	cof[13] = a[0] * a[9] * a[14] - a[0] * a[10] * a[13] - a[8] * a[1] * a[14]
		+ a[8] * a[2] * a[13] + a[12] * a[1] * a[10] - a[12] * a[2] * a[9];
	cof[14] = -a[0] * a[5] * a[14] + a[0] * a[6] * a[13] + a[4] * a[1] * a[14]
		- a[4] * a[2] * a[13] - a[12] * a[1] * a[6] + a[12] * a[2] * a[5];
	cof[15] = a[0] * a[5] * a[10] - a[0] * a[6] * a[9] - a[4] * a[1] * a[10]
		+ a[4] * a[2] * a[9] + a[8] * a[1] * a[6] - a[8] * a[2] * a[5];


	det = a[0] * cof[0] + a[1] * cof[4] + a[2] * cof[8] + a[3] * cof[12];


	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = cof[i * 4 + j] / det;
		}

	return result;
}

Matrix4x4 Transpose(Matrix4x4& m)
{
	Matrix4x4 result;

	float a11 = m.m[0][0]; float a12 = m.m[0][1]; float a13 = m.m[0][2]; float a14 = m.m[0][3];
	float a21 = m.m[1][0]; float a22 = m.m[1][1]; float a23 = m.m[1][2]; float a24 = m.m[1][3];
	float a31 = m.m[2][0]; float a32 = m.m[2][1]; float a33 = m.m[2][2]; float a34 = m.m[2][3];
	float a41 = m.m[3][0]; float a42 = m.m[3][1]; float a43 = m.m[3][2]; float a44 = m.m[3][3];

	result.m[0][0] = a11; result.m[0][1] = a21; result.m[0][2] = a31; result.m[0][3] = a41;
	result.m[1][0] = a12; result.m[1][1] = a22; result.m[1][2] = a32; result.m[1][3] = a42;
	result.m[2][0] = a13; result.m[2][1] = a23; result.m[2][2] = a33; result.m[2][3] = a43;
	result.m[3][0] = a14; result.m[3][1] = a24; result.m[3][2] = a34; result.m[3][3] = a44;

	return result;
}

Matrix4x4 MakeIdentit4x4()
{
	Matrix4x4 result;

	result.m[0][0] = 1; result.m[0][1] = 0; result.m[0][2] = 0; result.m[0][3] = 0;
	result.m[1][0] = 0;	result.m[1][1] = 1;	result.m[1][2] = 0;	result.m[1][3] = 0;
	result.m[2][0] = 0;	result.m[2][1] = 0;	result.m[2][2] = 1;	result.m[2][3] = 0;
	result.m[3][0] = 0;	result.m[3][1] = 0;	result.m[3][2] = 0;	result.m[3][3] = 1;

	return result;
}


Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result;

	result.m[0][0] = 1.0f; result.m[0][1] = 0.0f; result.m[0][2] = 0.0f; result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f; result.m[1][1] = 1.0f; result.m[1][2] = 0.0f; result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f; result.m[2][1] = 0.0f; result.m[2][2] = 1.0f; result.m[2][3] = 0.0f;
	result.m[3][0] = translate.x; result.m[3][1] = translate.y; result.m[3][2] = translate.z; result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result;
	result.m[0][0] = scale.x; result.m[0][1] = 0.0f;    result.m[0][2] = 0.0f;    result.m[0][3] = 0;
	result.m[1][0] = 0.0f;    result.m[1][1] = scale.y; result.m[1][2] = 0.0f;    result.m[1][3] = 0;
	result.m[2][0] = 0.0f;    result.m[2][1] = 0.0f;    result.m[2][2] = scale.z; result.m[2][3] = 0;
	result.m[3][0] = 0.0f;    result.m[3][1] = 0.0f;    result.m[3][2] = 0.0f;    result.m[3][3] = 1.0f;

	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	
	float x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	float y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	float z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	
	if (w != 0.0f) {
		x /= w;
		y /= w;
		z /= w;
	}

	return { x, y, z };
}

Vector3 Normalize(const Vector3& v) {
	float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0.0f) {
		return { 0.0f, 0.0f, 0.0f }; 
	}
	return { v.x / length, v.y / length, v.z / length };
}

Vector3 Multiply(float scalar, const Vector3& v) {
	return { v.x * scalar, v.y * scalar, v.z * scalar };
}


Matrix4x4 MakeRoateXMatrix(float radian)
{
	Matrix4x4 result = {};

	result.m[0][0] = 1.0f;
	result.m[1][1] = cosf(radian);
	result.m[1][2] = sinf(radian);
	result.m[2][1] = -sinf(radian);
	result.m[2][2] = cosf(radian);
	result.m[3][3] = 1.0f;

	return result;
}
Matrix4x4 MakeRoateYMatrix(float radian)
{
	Matrix4x4 result = {};

	result.m[0][0] = std::cosf(radian);
	result.m[0][2] = -std::sinf(radian);
	result.m[1][1] = 1.0f;
	result.m[2][0] = std::sin(radian);
	result.m[2][2] = std::cosf(radian);
	result.m[3][3] = 1.0f;

	return result;
}
Matrix4x4 MakeRoateZMatrix(float radian)
{
	Matrix4x4 result = {};

	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = std::sinf(radian);
	result.m[1][0] = -std::sinf(radian);
	result.m[1][1] = std::cosf(radian);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	return result;
}



Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result;
	result.m[0][0] = (1.0f/aspectRatio)*(1.0f/tanf(fovY/2.0f)); result.m[0][1] = 0.0f;    result.m[0][2] = 0.0f;    result.m[0][3] = 0;
	result.m[1][0] = 0.0f;    result.m[1][1] = 1.0f / tanf(fovY / 2.0f); result.m[1][2] = 0.0f;    result.m[1][3] = 0;
	result.m[2][0] = 0.0f;    result.m[2][1] = 0.0f;    result.m[2][2] = farClip/ (farClip - nearClip); result.m[2][3] = 1.0f;
	result.m[3][0] = 0.0f;    result.m[3][1] = 0.0f;    result.m[3][2] = -nearClip*farClip / (farClip-nearClip );    result.m[3][3] = 0.0f;

	return result;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result;
	result.m[0][0] = 2.0f/(right-left); result.m[0][1] = 0.0f;    result.m[0][2] = 0.0f;    result.m[0][3] = 0;
	result.m[1][0] = 0.0f;    result.m[1][1] = 2.0f/(top-bottom); result.m[1][2] = 0.0f;    result.m[1][3] = 0;
	result.m[2][0] = 0.0f;    result.m[2][1] = 0.0f;    result.m[2][2] = 1/(farClip-nearClip); result.m[2][3] = 0;
	result.m[3][0] = (left+right)/(left-right);    result.m[3][1] = (top +bottom)/ (bottom-top);    result.m[3][2] = nearClip/(nearClip-farClip);    result.m[3][3] = 1.0f;

	return result;

}


Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result;
	result.m[0][0] =  width/ 2.0f; result.m[0][1] = 0.0f;    result.m[0][2] = 0.0f;    result.m[0][3] = 0;
	result.m[1][0] = 0.0f;    result.m[1][1] = -height/2.0f; result.m[1][2] = 0.0f;    result.m[1][3] = 0;
	result.m[2][0] = 0.0f;    result.m[2][1] = 0.0f;    result.m[2][2] = maxDepth-minDepth; result.m[2][3] = 0;
	result.m[3][0] = left +  (width/2.0f);    result.m[3][1] = top + height/2.0f;    result.m[3][2] = minDepth;    result.m[3][3] = 1.0f;

	return result;
}



Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate)
{
	
	Matrix4x4 scaleMatrix = {};
	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[2][2] = scale.z;
	scaleMatrix.m[3][3] = 1.0f;

	
	Matrix4x4 rotateXMatrix = MakeRoateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRoateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRoateZMatrix(rotate.z);

	Matrix4x4 rotateMatrix = Multiply(Multiply(rotateXMatrix, rotateYMatrix), rotateZMatrix);

	
	Matrix4x4 translateMatrix = {};
	translateMatrix.m[0][0] = 1.0f;
	translateMatrix.m[1][1] = 1.0f;
	translateMatrix.m[2][2] = 1.0f;
	translateMatrix.m[3][3] = 1.0f;
	translateMatrix.m[3][0] = translate.x;
	translateMatrix.m[3][1] = translate.y;
	translateMatrix.m[3][2] = translate.z;

	
	Matrix4x4 affineMatrix = Multiply(Multiply(scaleMatrix, rotateMatrix), translateMatrix);

	return affineMatrix;
}


void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix)
{
	static const int kRowHeight = 20;
	static const int kColumnWidth = 60;

	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}


void VectorScreenPrintf(int x, int y, const Vector3 vector, const char* label)
{
	static const int kColumnWidth = 60;
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z); 
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);

}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.y * v2.z - v1.z * v2.y; result.y = v1.z * v2.x - v1.x * v2.z; result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

float Length(const Vector3& v) {
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}


//Vector3 Project(const Vector3& v1, const Vector3& v2)
//{
//	Vector3 result;
//	 result.x= ((v2.x*v2.x+v2.y*v2.y+v2.z*v2.z)  * (1.0f/v1.x* v2.x + v1.y * v2.y + v1.z * v2.z))*v2.x;
//	 result.y = ((v2.x * v2.x + v2.y * v2.y + v2.z * v2.z) * (1.0f / v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)) * v2.y;
//	 result.z = ((v2.x * v2.x + v2.y * v2.y + v2.z * v2.z) * (1.0f / v1.x * v2.x + v1.y * v2.y + v1.z * v2.z)) * v2.z;
//
//	 return result;
//
//}

Vector3 Subtract(const Vector3& a, const Vector3& b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

Vector3 Add(const Vector3& a, const Vector3& b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector3 Multiply(const Vector3& v, float scalar) {
	return { v.x * scalar, v.y * scalar, v.z * scalar };
}


Vector3 Project(const Vector3& v1, const Vector3& v2) {
	float dot = v1.Dot(v2);
	float lenSq = v2.Dot(v2);
	if (lenSq == 0.0f) return { 0, 0, 0 };
	return v2 * (dot / lenSq);
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 a = segment.origin;
	Vector3 ab = segment.diff;

	Vector3 ap = point - a;

	float abLenSq = ab.Dot(ab);
	if (abLenSq == 0.0f) {
		
		return a;
	}

	float t = ap.Dot(ab) / abLenSq;

	
	t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f : t;

	return a + ab * t;
}

float Dot(const Vector3& a, const Vector3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}


bool IsCollision(const Sphere& s1, const Sphere& s2) {
	Vector3 diff = s1.center - s2.center;
	float distanceSq = diff.Dot(diff);
	float radiusSum = s1.radius + s2.radius;
	return distanceSq < (radiusSum * radiusSum);
}

bool IsCollision(const Sphere& sphere, const Plane& plane) {
	
	float dist = Dot(plane.normal, sphere.center) - plane.distance;
	return std::abs(dist) <= sphere.radius;
}

bool IsCollision(const Segment& line, const Plane& plane) {
	//方向ベクトル
	Vector3 dir = line.diff;

	//分母：平面法線と線の向きの内積
	float dot = Dot(plane.normal, dir);

	//平行な場合は交差しない
	if (dot == 0.0f) {
		return false;
	}

	//tを求める（上記数式に基づく）
	float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;

	//線分外なら衝突していない
	if (t < 0.0f || t > 1.0f) {
		return false;
	}

	
	return true;
}



bool IsCollision(const Triangle& triangle, const Segment& segment) 
{
	// ステップ1：三角形の平面を構成
	Vector3 edge1 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 edge2 = Subtract(triangle.vertices[2], triangle.vertices[0]);
	Vector3 normal = Normalize(Cross(edge1, edge2));
	float distance = Dot(normal, triangle.vertices[0]);

	Plane plane = { normal, distance };

	// ステップ2：線分と平面が衝突するかチェック
	Vector3 dir = segment.diff;
	float dot = Dot(plane.normal, dir);

	if (dot == 0.0f) return false; // 平行なら交差しない

	// t計算（必要なときだけ）
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	// 線分外なら交点は存在しない
	if (t < 0.0f || t > 1.0f) return false;

	// ステップ3：交点を内部的に計算
	Vector3 intersection = Add(segment.origin, Multiply(dir, t));

	// ステップ4：三角形内かをクロス積で判定
	Vector3 c0 = Cross(Subtract(triangle.vertices[1], triangle.vertices[0]), Subtract(intersection, triangle.vertices[0]));
	Vector3 c1 = Cross(Subtract(triangle.vertices[2], triangle.vertices[1]), Subtract(intersection, triangle.vertices[1]));
	Vector3 c2 = Cross(Subtract(triangle.vertices[0], triangle.vertices[2]), Subtract(intersection, triangle.vertices[2]));

	if (Dot(normal, c0) >= 0 && Dot(normal, c1) >= 0 && Dot(normal, c2) >= 0) {
		return true; // 三角形内部
	}

	return false; // 外部
}

bool IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	
	if (
		//x軸
		(aabb1.min.x <= aabb2.max.x &&  aabb1.max.x >= aabb2.min.x) &&

		//y軸
		(aabb1.min.y <= aabb2.max.y &&  aabb1.max.y >= aabb2.min.y) &&

		//z軸
		(aabb1.min.z <= aabb2.max.z &&  aabb1.max.z >= aabb2.min.z)
		)
	{ 
		//衝突
		return true;
	}
	else
	{
		return false;
	}

}

bool IsCollision(const AABB& aabb, const Sphere& sphere)
{
	//最近接点を求める
	Vector3 closestPoint
	{
		std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
		std::clamp(sphere.center.y,aabb.min.y,aabb.max.y),
		std::clamp(sphere.center.z,aabb.min.z,aabb.max.z),
	};

	//最近接点と球の中心との距離を求める
	float distance = Length(closestPoint - sphere.center);

	//距離が半径よりも小さければ衝突
	if (distance <= sphere.radius)
	{
		//衝突
		return true;
	}
	else
	{
		return false;
	}
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color)
{
	Matrix4x4 vpvpMatrix = Multiply(viewProjectionMatrix, viewportMatrix);

	// min = (xmin, ymin, zmin), max = (xmax, ymax, zmax)
	Vector3 p0 = { aabb.min.x, aabb.min.y, aabb.min.z };
	Vector3 p1 = { aabb.max.x, aabb.min.y, aabb.min.z };
	Vector3 p2 = { aabb.min.x, aabb.max.y, aabb.min.z };
	Vector3 p3 = { aabb.max.x, aabb.max.y, aabb.min.z };
	Vector3 p4 = { aabb.min.x, aabb.min.y, aabb.max.z };
	Vector3 p5 = { aabb.max.x, aabb.min.y, aabb.max.z };
	Vector3 p6 = { aabb.min.x, aabb.max.y, aabb.max.z };
	Vector3 p7 = { aabb.max.x, aabb.max.y, aabb.max.z };

	p0 = Transform(p0, vpvpMatrix);
	p1 = Transform(p1, vpvpMatrix);
	p2 = Transform(p2, vpvpMatrix);
	p3 = Transform(p3, vpvpMatrix);
	p4 = Transform(p4, vpvpMatrix);
	p5 = Transform(p5, vpvpMatrix);
	p6 = Transform(p6, vpvpMatrix);
	p7 = Transform(p7, vpvpMatrix);

	Novice::DrawLine(static_cast<int>(p0.x), static_cast<int>(p0.y), static_cast<int>(p1.x), static_cast<int>(p1.y), color);
	Novice::DrawLine(static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p3.x), static_cast<int>(p3.y), color);
	Novice::DrawLine(static_cast<int>(p3.x), static_cast<int>(p3.y), static_cast<int>(p2.x), static_cast<int>(p2.y), color);
	Novice::DrawLine(static_cast<int>(p2.x), static_cast<int>(p2.y), static_cast<int>(p0.x), static_cast<int>(p0.y), color);

	Novice::DrawLine(static_cast<int>(p4.x), static_cast<int>(p4.y), static_cast<int>(p5.x), static_cast<int>(p5.y), color);
	Novice::DrawLine(static_cast<int>(p5.x), static_cast<int>(p5.y), static_cast<int>(p7.x), static_cast<int>(p7.y), color);
	Novice::DrawLine(static_cast<int>(p7.x), static_cast<int>(p7.y), static_cast<int>(p6.x), static_cast<int>(p6.y), color);
	Novice::DrawLine(static_cast<int>(p6.x), static_cast<int>(p6.y), static_cast<int>(p4.x), static_cast<int>(p4.y), color);

	Novice::DrawLine(static_cast<int>(p0.x), static_cast<int>(p0.y), static_cast<int>(p4.x), static_cast<int>(p4.y), color);
	Novice::DrawLine(static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p5.x), static_cast<int>(p5.y), color);
	Novice::DrawLine(static_cast<int>(p2.x), static_cast<int>(p2.y), static_cast<int>(p6.x), static_cast<int>(p6.y), color);
	Novice::DrawLine(static_cast<int>(p3.x), static_cast<int>(p3.y), static_cast<int>(p7.x), static_cast<int>(p7.y), color);

}


void DrawTriangle(
	const Triangle& triangle,
	const Matrix4x4& viewProjectionMatrix,
	const Matrix4x4& viewportMatrix,
	int color
) {
	// 各頂点をワールド → ビュー → プロジェクション → ビューポートへ変換
	Vector3 p0 = Transform(Transform(triangle.vertices[0], viewProjectionMatrix), viewportMatrix);
	Vector3 p1 = Transform(Transform(triangle.vertices[1], viewProjectionMatrix), viewportMatrix);
	Vector3 p2 = Transform(Transform(triangle.vertices[2], viewProjectionMatrix), viewportMatrix);

	// 三角形の辺を描画
	Novice::DrawTriangle((int)p0.x, (int)p0.y, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, color, kFillModeWireFrame);


}



Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y, vector.x, 0.0f };  
	}
	return { 0.0f, -vector.z, vector.y };      
}

void DrawPlane(
	const Plane& plane,
	const Matrix4x4& viewProjectionMatrix,
	const Matrix4x4& viewportMatrix,
	int color)
{
	
	Vector3 center = Multiply(plane.distance, plane.normal); 

	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);     
		Vector3 point = Add(center, extend);                    
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix); 
	}

	
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[3].x), int(points[3].y), color);

	

}


void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;           
	const uint32_t kSubdivision = 10;            
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision); 

	
	Matrix4x4 vpvpMatrix = Multiply(viewProjectionMatrix, viewportMatrix);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		float x = -kGridHalfWidth + xIndex * kGridEvery;

		
		Vector3 start = { x, 0, -kGridHalfWidth };
		Vector3 end = { x, 0,  kGridHalfWidth };
		
		
		
	
		
			 
		Vector3 screenStart = Transform(start, vpvpMatrix);
		Vector3 screenEnd = Transform(end, vpvpMatrix);

		
		Novice::DrawLine(int(screenStart.x), int(screenStart.y),
			int(screenEnd.x), int(screenEnd.y),
			WHITE);
	}

	
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		
			float z = -kGridHalfWidth + zIndex * kGridEvery;

			Vector3 start = { -kGridHalfWidth, 0.0f, z };
			Vector3 end = { +kGridHalfWidth, 0.0f, z };

			Vector3 screenStart = Transform(start, vpvpMatrix);
			Vector3 screenEnd = Transform(end, vpvpMatrix);

			Novice::DrawLine(
				int(screenStart.x), int(screenStart.y),
				int(screenEnd.x), int(screenEnd.y),
				WHITE
			);
		
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color) {
	const uint32_t kSubdivision = 16;                    
	const float kLonEvery = 2.0f * float(M_PI) / kSubdivision; 
	const float kLatEvery = float(M_PI) / kSubdivision;        

	
	Matrix4x4 vpvpMatrix = Multiply(viewProjectionMatrix, viewportMatrix);

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;

			
			Vector3 a = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};
			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(lat + kLatEvery) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat + kLatEvery),
				sphere.center.z + sphere.radius * cosf(lat + kLatEvery) * sinf(lon)
			};
			Vector3 c = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon + kLonEvery),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon + kLonEvery)
			};

			
			Vector3 screenA = Transform(a, vpvpMatrix);
			Vector3 screenB = Transform(b, vpvpMatrix);
			Vector3 screenC = Transform(c, vpvpMatrix);

			
			Novice::DrawLine((int)screenA.x, (int)screenA.y, (int)screenB.x, (int)screenB.y, color);
			Novice::DrawLine((int)screenA.x, (int)screenA.y, (int)screenC.x, (int)screenC.y, color);
		}
	}
}


//void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)