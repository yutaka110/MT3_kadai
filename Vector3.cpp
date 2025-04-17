#include"Vector3.h"
#include"math.h"

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

//積
Vector3 Multiply(float scalar, const Vector3& v)
{
	Vector3 result;
	result.x = v.x*scalar;
	result.y = v.y*scalar;
	result.z = v.z*scalar;
	return result;
}

//内積
float Dot(const Vector3& v1, const Vector3& v2)
{
	float result;
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;

}

//長さ
float Length(const Vector3& v)
{
	float result;
	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

//初期化
Vector3 Normalize(const Vector3& v)
{
	
		Vector3 result;

		
		float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

		
		if (length != 0.0f) {
			result.x = v.x / length;
			result.y = v.y / length;
			result.z = v.z / length;
		}
		else {
			
			result.x = 0.0f;
			result.y = 0.0f;
			result.z = 0.0f;
		}

		return result;
	
}

//3次元ベクトルの数値表示
void VectorScreenPrintf(int x, int y, const Vector3 vector, const char* label)
{
	static const int kColumnWidth = 60;
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);

}