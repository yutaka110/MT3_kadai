#include <Novice.h>
#include<cstdint>
#include"matrix4x4.h"
#include <imgui.h>
#include"Spring.h"
#include<math.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include"Pendulum.h"
const char kWindowTitle[] = "LE2B_17_タケイ_ユタカ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//変数の初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	//Vector3 rotate{ 0.0f,2.0f,0.0f };
	Vector3 translate{};

	// カメラの位置（Z軸マイナス方向に引いている）
	Vector3 cameraPosition{ 0.0f, 0.0f, -5.0f };
	Vector3 cameraTranslate{ 0.0f, 0.0f, 0.0f };
	Vector3 cameraRotate{ -0.2f,0.0f,0.0f };

	// ローカル座標系の三角形の3頂点
	Vector3 kLocalVertices[3] = {
		{ 0.0f,  0.5f, 0.0f },  // 上
		{ 0.5f, -0.5f, 0.0f },  // 右下
		{ -0.5f, -0.5f, 0.0f }  // 左下
	};

	Sphere sphere;
	sphere.center = { 0.01f,0.01f,0.01f };
	sphere.radius = 0.1f;

	Sphere sphere2;
	sphere2.center = { 0.01f,0.01f,0.01f };
	sphere2.radius = 0.1f;

	Vector3 v1{ 1.2f, -3.9f, 2.5f };
	Vector3 v2{ 2.8f, 0.4f, -1.3f };
	
	Segment segment{ {-2.0f, -1.0f, 0.0f}, {3.0f, 2.0f, 2.0f} };
	Vector3 point{ -1.5f, 0.6f, 0.6f };

	Plane plane;
	plane.normal = Normalize({ 0.0f, 1.0f, 0.0f });  // 上向きの単位ベクトル
	plane.distance = 0.0f;                        // 原点を通る平面

	Triangle triangle = {
	{
		{ 0.0f,  0.5f, 0.0f },  // 上
		{ 0.5f, -0.5f, 0.0f },  // 右下
		{ -0.5f, -0.5f, 0.0f }  // 左下
	}
	};

	AABB aabb1
	{
		.min{-0.5f,-0.5f,-0.5f},
		.max{0.0f,0.0f,0.0f},
	};

	AABB aabb2
	{
		.min{0.2f,0.2f,0.2f},
		.max{1.0f,1.0f,1.0f},
	};

	Vector3 controlPoints[3] = {
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f},
	};

	Vector3 translates[3] = {
	{0.2f, 1.0f, 0.0f},
	{0.4f, 0.0f, 0.0f},
	{0.3f, 0.0f, 0.0f},
	};

	Vector3 rotates[3] = {
		{0.0f, 0.0f, -6.8f},
		{0.0f, 0.0f, -1.4f},
		{0.0f, 0.0f, 0.0f},
	};

	Vector3 scales[3] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
	};

	Spring spring{};
	spring.anchor = { 0.0f, 0.0f, 0.0f };
	spring.naturalLength = 1.0f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	Ball ball{};
	ball.position = { 1.2f, 0.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	float angularVelocity = 3.14f;
	float angle = 0.0f;
	float radius = 0.8f;

	//円の中心
	Vector3 center = { 0.0f, 0.0f, 0.0f };

	//現在の位置(後で更新)
	Vector3 position = {};  

	Pendulum pendulum;

	pendulum.anchor = { 0.0f, 1.0f, 0.0f };
	pendulum.length = 0.8f;
	pendulum.angle = 0.7f;
	pendulum.angularVelocity = 0.0f;
	pendulum.angularAcceleration = 0.0f;

	Vector3 pendulumTip = { 0.0f, 0.0f, 0.0f };
	bool isPendulumActive = false;


	Vector3 a{ 0.2f, 1.0f, 0.0f };
	Vector3 b{ 2.4f, 3.1f, 1.2f };
	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = b * 2.4f;
	Vector3 rotate{ 0.4f, 1.43f, -0.8f };

	Matrix4x4 rotateXMatrix = MakeRoateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRoateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRoateZMatrix(rotate.z);
	Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;


	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewportMatrix;

	//デルタタイム
	float deltaTime = 1.0f / 60.0f;
	



	
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//キーの入力
		if (keys[DIK_W])
		{
			translate.y += 0.05f;
		}

		if (keys[DIK_S])
		{
			translate.y -= 0.05f;
		}

		if (keys[DIK_A])
		{
			translate.x -= 0.05f;
		}

		if (keys[DIK_D])
		{
			translate.x += 0.05f;
		}

		// 毎フレーム自動でY軸回転
		//rotate.y += 0.02f;

		//クロス積の計算
		Vector3 cross = Cross(v1, v2);
		

		// point を線分に射影したベクトル
		Vector3 project = Project(Subtract(point, segment.origin), segment.diff);


		// 線分上の最近接点
		Vector3 closestPoint = ClosestPoint(point, segment);

		Sphere pointSphere{ point, 0.01f };        // 点の可視化用の球（赤）
		Sphere closestPointSphere{ closestPoint, 0.01f }; // 最近接点の可視化用の球（黒）

		Sphere controlPointsSphere[3];
		controlPointsSphere[0] = { controlPoints[0],0.01f };
		controlPointsSphere[1] = { controlPoints[1],0.01f };
		controlPointsSphere[2] = { controlPoints[2],0.01f };

		Matrix4x4 shoulderMatrix = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 elbowMatrixLocal = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		Matrix4x4 handMatrixLocal = MakeAffineMatrix(scales[2], rotates[2], translates[2]);

		// 肘は肩に親子付け(肩→肘)
		Matrix4x4 elbowMatrix = Multiply(elbowMatrixLocal, shoulderMatrix);
		// 手は肘に親子付け(肩→肘→手）
		Matrix4x4 handMatrix = Multiply(handMatrixLocal, elbowMatrix);

		Vector3 shoulderWorldPos = Transform({ 0, 0, 0 }, shoulderMatrix);
		Vector3 elbowWorldPos = Transform({ 0, 0, 0 }, elbowMatrix);
		Vector3 handWorldPos = Transform({ 0, 0, 0 }, handMatrix);

		Vector3 diff = ball.position - spring.anchor;
		float length = Length(diff);
		if (length != 0.0f) {
			Vector3 direction = Normalize(diff);
			Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
			Vector3 displacement = length * (ball.position - restPosition);
			Vector3 restoringForce = -spring.stiffness * displacement;
			Vector3 dampingForce = -spring.dampingCoefficient * ball.velocity;
			Vector3 force = restoringForce + dampingForce;
			ball.acceleration = force / ball.mass;
			


		}

		// 加速度や速度もどちらも秒を基準とした値である
		// それが 1/60秒間 (deltaTime) 適用されたと考える
		ball.velocity += ball.acceleration * deltaTime;
		ball.position += ball.velocity * deltaTime;

		

		// 角度更新（角速度 × Δt）
		angle += angularVelocity * deltaTime;

		// 位置更新（2D円運動: XY平面）
		position.x = center.x + std::cos(angle) * radius;
		position.y = center.y + std::sin(angle) * radius;
		position.z = center.z;

		if (isPendulumActive) {
			pendulum.angularAcceleration =
				-(9.8f / pendulum.length) * std::sin(pendulum.angle);

			pendulum.angularVelocity += pendulum.angularAcceleration * deltaTime;
			pendulum.angle += pendulum.angularVelocity * deltaTime;

			// pは振り子の先端の位置。取り付けたいものを取り付ければ良い
			pendulumTip.x = pendulum.anchor.x + std::sin(pendulum.angle) * pendulum.length;
			pendulumTip.y = pendulum.anchor.y - std::cos(pendulum.angle) * pendulum.length;
			pendulumTip.z = pendulum.anchor.z;
		}


		//Vector3 p0p1=Lerp

	/*	DrawSphere(pointSphere, worldViewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(closestPointSphere, worldViewProjectionMatrix, viewportMatrix, BLACK);*/


		// 各種行列の計算
	   worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
	   cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
	   viewMatrix = Inverse(cameraMatrix);
	   projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	   worldViewProjectionMatrix = Multiply(Multiply(worldMatrix, viewMatrix), projectionMatrix);
	   viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	   // anchor → ball.position を線で結ぶ（ばね表示）
	   Vector3 anchorScreen = Transform(Transform(spring.anchor, worldViewProjectionMatrix), viewportMatrix);
	   Vector3 ballScreen = Transform(Transform(ball.position, worldViewProjectionMatrix), viewportMatrix);

	   Vector3 screenCenter = Transform(Transform(center, worldViewProjectionMatrix), viewportMatrix);
	   Vector3 screenPos = Transform(Transform(position, worldViewProjectionMatrix), viewportMatrix);

	   Vector3 screenPendulumAnchor= Transform(Transform(pendulum.anchor, worldViewProjectionMatrix), viewportMatrix);
	   Vector3 screenPendulumTip = Transform(Transform(pendulumTip, worldViewProjectionMatrix), viewportMatrix);
		/*Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}*/


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


	   Vector3 start = Transform(Transform(segment.origin, worldViewProjectionMatrix), viewportMatrix);
	   Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), worldViewProjectionMatrix), viewportMatrix);
	  
	  

	   //グリッドの描画
	   DrawGrid(worldViewProjectionMatrix, viewportMatrix);

	   Vector3 shoulderScreen = Transform(shoulderWorldPos, worldViewProjectionMatrix);
	   shoulderScreen = Transform(shoulderScreen, viewportMatrix);

	   Vector3 elbowScreen = Transform(elbowWorldPos, worldViewProjectionMatrix);
	   elbowScreen = Transform(elbowScreen, viewportMatrix);

	   Vector3 handScreen = Transform(handWorldPos, worldViewProjectionMatrix);
	   handScreen = Transform(handScreen, viewportMatrix);

	   // 球の描画（肩：赤、肘：緑、手：青）
	   DrawSphere({ shoulderWorldPos, 0.05f }, worldViewProjectionMatrix, viewportMatrix, RED);
	   DrawSphere({ elbowWorldPos, 0.05f }, worldViewProjectionMatrix, viewportMatrix, GREEN);
	   DrawSphere({ handWorldPos, 0.05f }, worldViewProjectionMatrix, viewportMatrix, BLUE);

	   // 関節をつなぐ線の描画
	   Novice::DrawLine((int)shoulderScreen.x, (int)shoulderScreen.y,
		   (int)elbowScreen.x, (int)elbowScreen.y, WHITE);
	   Novice::DrawLine((int)elbowScreen.x, (int)elbowScreen.y,
		   (int)handScreen.x, (int)handScreen.y, WHITE);

	   ////バネの線分描画
	   //Novice::DrawLine(
		  // static_cast<int>(anchorScreen.x), static_cast<int>(anchorScreen.y),
		  // static_cast<int>(ballScreen.x), static_cast<int>(ballScreen.y),
		  // BLACK
	   //);

	   ////バネの球描画
	   //DrawSphere({ ball.position, 0.05f }, worldViewProjectionMatrix, viewportMatrix, BLUE);

	   ////円運動線分描画
	   //Novice::DrawLine(
		  // static_cast<int>(screenCenter.x), static_cast<int>(screenCenter.y),
		  // static_cast<int>(screenPos.x), static_cast<int>(screenPos.y),
		  // RED
	   //);

	   //振り子の線分描画
	   Novice::DrawLine(
		   static_cast<int>(screenPendulumAnchor.x), static_cast<int>(screenPendulumAnchor.y),
		   static_cast<int>(screenPendulumTip.x), static_cast<int>(screenPendulumTip.y),
		   RED
	   );
	   DrawSphere({ pendulumTip,0.05f }, worldViewProjectionMatrix, viewportMatrix, GREEN);

	   //球と球の当たり判定
	/*   if (IsCollision(sphere, sphere2))
	   {
		   DrawSphere(sphere2, worldViewProjectionMatrix, viewportMatrix, RED);
	   }
	   else
	   {
		   DrawSphere(sphere2, worldViewProjectionMatrix, viewportMatrix, WHITE);
	   }

	   DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, WHITE);*/

	   

	   ////平面と球の当たり判定
    //   if (IsCollision(sphere, plane))
	   //{
		  // DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, RED);
	   //}
	   //else
	   //{
		  // DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, WHITE);
	   //}

	   //線と平面の当たり判定
	  /* if (IsCollision(segment, plane))
	   {
		   DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, RED);
		  
	   }
	   else
	   {
		   DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, WHITE);
	   }

	   DrawTriangle(triangle, worldViewProjectionMatrix, viewportMatrix, WHITE);*/

	   //DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, WHITE);

	  /* if (IsCollision(triangle, segment))
	   {
		   Novice::DrawLine(
			   int(start.x), int(start.y),
			   int(end.x), int(end.y),
			   RED
		   );
	   }
	   else
	   {
		   Novice::DrawLine(
			   int(start.x), int(start.y),
			   int(end.x), int(end.y),
			   WHITE
		   );
	   }*/

	   //AABBと線分の衝突判定
	   /*if (IsCollision(aabb1, segment))
	   {
		   Novice::DrawLine(
			   int(start.x), int(start.y),
			   int(end.x), int(end.y),
			   RED
		   );
	   }
	   else
	   {
		   Novice::DrawLine(
			   int(start.x), int(start.y),
			   int(end.x), int(end.y),
			   WHITE
		   );
	   }*/

	   //AABBの描画
	   /*if (IsCollision(aabb1, aabb2))
	   {
		   DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, RED);
	   }
	   else
	   {
		   DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, WHITE);
	   }*/

	  // DrawAABB(aabb2, worldViewProjectionMatrix, viewportMatrix, WHITE);

	   ////球とAABBの衝突判定
	   //if (IsCollision(aabb1, sphere))
	   //{
		  // DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, RED);
	   //}
	   //else
	   //{
		  // DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, WHITE);
	   //}

		//// 描画
		//Novice::DrawTriangle(
		//	int(screenVertices[0].x), int(screenVertices[0].y),
		//	int(screenVertices[1].x), int(screenVertices[1].y),
		//	int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid
		//);

	   DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2], worldViewProjectionMatrix, viewportMatrix, WHITE);
	   for (int i = 0; i < 3; ++i) {
		   DrawSphere(controlPointsSphere[i], worldViewProjectionMatrix, viewportMatrix, WHITE);
	   }
		VectorScreenPrintf(0, 0, cross, "Cross");

		ImGui::Begin("Window");

		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		// 平面の編集
		ImGui::DragFloat3("Plane.Normal", &plane.normal.x, 0.01f);

		//Segmentの編集
		ImGui::DragFloat3("Segment.Origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("Segment.Diff", &segment.diff.x, 0.01f);

		//正規化
		plane.normal = Normalize(plane.normal); 

		
		ImGui::DragFloat3("AABB1 Min", &aabb1.min.x, 0.01f);
		ImGui::DragFloat3("AABB1 Max", &aabb1.max.x, 0.01f);

		ImGui::DragFloat3("AABB2 Min", &aabb2.min.x, 0.01f);
		ImGui::DragFloat3("AABB2 Max", &aabb2.max.x, 0.01f);

		ImGui::Text("Bezier Control Points");
		ImGui::DragFloat3("ControlPoint0", &controlPoints[0].x, 0.01f);
		ImGui::DragFloat3("ControlPoint1", &controlPoints[1].x, 0.01f);
		ImGui::DragFloat3("ControlPoint2", &controlPoints[2].x, 0.01f);

		ImGui::Separator();
		ImGui::Text("Joint Transforms");

		//0:肩,1:肘,2:手
		ImGui::DragFloat3("Translate 0", &translates[0].x, 0.01f);
		ImGui::DragFloat3("Rotate 0", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("Scale 0", &scales[0].x, 0.01f);

		ImGui::DragFloat3("Translate 1", &translates[1].x, 0.01f);
		ImGui::DragFloat3("Rotate 1", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("Scale 1", &scales[1].x, 0.01f);

		ImGui::DragFloat3("Translate 2", &translates[2].x, 0.01f);
		ImGui::DragFloat3("Rotate 2", &rotates[2].x, 0.01f);
		ImGui::DragFloat3("Scale 2", &scales[2].x, 0.01f);

		ImGui::Text("c:%f, %f, %f", c.x, c.y, c.z);
		ImGui::Text("d:%f, %f, %f", d.x, d.y, d.z);
		ImGui::Text("e:%f, %f, %f", e.x, e.y, e.z);

		ImGui::Text(
			"matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
			rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3],
			rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]
		);

		//spring
		ImGui::Text("SPring");
		ImGui::DragFloat("Natural Length", &spring.naturalLength, 0.01f, 0.0f);
		ImGui::DragFloat("Stiffness", &spring.stiffness, 0.1f, 0.0f);
		ImGui::DragFloat("Damping", &spring.dampingCoefficient, 0.1f, 0.0f);
		if (ImGui::Button("Reset")) {
			// Spring側は必要ならリセット
			spring.anchor = { 0.0f, 0.0f, 0.0f };
			

			// Ballの状態リセット
			ball.position = { 1.2f, 0.0f, 0.0f };
			ball.velocity = { 0.0f, 0.0f, 0.0f };
			ball.acceleration = { 0.0f, 0.0f, 0.0f };
			ball.mass = 2.0f;
			ball.radius = 0.05f;
		}

		//pendulum
		ImGui::Text("Pendulum");
		if (ImGui::Button("Start Pendulum")) {
			isPendulumActive = true;
		}

		if (ImGui::Button("Stop Pendulum")) {
			isPendulumActive = false;
		}

		if (ImGui::Button("Reset Pendulum")) {
			isPendulumActive = false;
			pendulum.angle = 0.7f;
			pendulum.angularVelocity = 0.0f;
			pendulum.angularAcceleration = 0.0f;

			pendulumTip.x = pendulum.anchor.x + std::sin(pendulum.angle) * pendulum.length;
			pendulumTip.y = pendulum.anchor.y - std::cos(pendulum.angle) * pendulum.length;
			pendulumTip.z = pendulum.anchor.z;
		}

		// 最小値が最大値を超えないように制限
		// x成分の修正
		if (aabb1.min.x > aabb1.max.x) {
			float temp = aabb1.min.x;
			aabb1.min.x = aabb1.max.x;
			aabb1.max.x = temp;
		}

		// y成分の修正
		if (aabb1.min.y > aabb1.max.y) {
			float temp = aabb1.min.y;
			aabb1.min.y = aabb1.max.y;
			aabb1.max.y = temp;
		}

		// z成分の修正
		if (aabb1.min.z > aabb1.max.z) {
			float temp = aabb1.min.z;
			aabb1.min.z = aabb1.max.z;
			aabb1.max.z = temp;
		}


		ImGui::End();
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
