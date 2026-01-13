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

	/*Vector3 operator-(const Vector3& rhs) const {
		return { x - rhs.x, y - rhs.y, z - rhs.z };
	}

	Vector3 operator+(const Vector3& rhs) const {
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	Vector3 operator*(float scalar) const {
		return { x * scalar, y * scalar, z * scalar };
	}*/

	float Dot(const Vector3& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

};

struct Sphere
{
	Vector3 center;
	float radius;
};

struct Line
{
	Vector3 origin;
	Vector3 diff;
};

struct Ray
{
	Vector3 origin;
	Vector3 diff;
};

struct Segment
{
	Vector3 origin;
	Vector3 diff;
};

struct Plane 
{
	Vector3 normal;  
	float distance; 
};

struct Triangle
{
	Vector3 vertices[3];
};

struct AABB
{
	Vector3 min;
	Vector3 max;
};

struct Capsule {
	Segment segment;
	float radius;
};

// 構造体の外に書く！
inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
	return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
	return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

inline Vector3 operator*(const Vector3& v, float s) {
	return { v.x * s, v.y * s, v.z * s };
}


inline Vector3 operator/(const Vector3& v, float s) {
	return { v.x / s, v.y / s, v.z / s };
}

inline Vector3 operator-(const Vector3& v) {
	return { -v.x, -v.y, -v.z };
}

inline Vector3& operator+=(Vector3& lhs, const Vector3& rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}



// float * Vector3（今回追加する必要あり）
inline Vector3 operator*(float s, const Vector3& v) {
	return v * s; // 上の関数を呼び出し
}




Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);
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

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
Vector3 Subtract(const Vector3& a, const Vector3& b);
Vector3 Add(const Vector3& a, const Vector3& b);
Vector3 Multiply(const Vector3& v, float scalar);
float Dot(const Vector3& a, const Vector3& b);
float Length(const Vector3& v);

Vector3 Normalize(const Vector3& v);
Vector3 Multiply(float scalar, const Vector3& v);
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);
void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);
bool IsCollision(const Sphere& s1, const Sphere& s2);
bool IsCollision(const Sphere& sphere, const Plane& plane);
bool IsCollision(const Segment& segment, const Plane& plane);
bool IsCollision(const Triangle& triangle, const Segment& segment);
bool IsCollision(const AABB& aabb1, const AABB& aabb2);
bool IsCollision(const AABB& aabb, const Sphere& sphere);
bool IsCollision(const AABB& aabb, const Segment& segment);
Vector3 Perpendicular(const Vector3& vector);
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);
void DrawTriangle(const Triangle& triangle,const Matrix4x4& viewProjectionMatrix,const Matrix4x4& viewportMatrix,	int color);
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, int color);
void VectorScreenPrintf(int x, int y, const Vector3 vector, const char* label);
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix);
Vector3 Cross(const Vector3& v1, const Vector3& v2);
Vector3 Reflect(const Vector3& input, const Vector3& normal);

//=============================================================
//---------------------------MT4-------------------------------
//=============================================================

//--------------------------01_01------------------------------
Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);
Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to);
