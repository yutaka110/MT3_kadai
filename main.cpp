#include <Novice.h>
#include<cstdint>
#include"matrix4x4.h"
#include <imgui.h>

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

	Vector3 rotate{ 0.0f,2.0f,0.0f };
	Vector3 translate{};

	// カメラの位置（Z軸マイナス方向に引いている）
	Vector3 cameraPosition{ 0.0f, 0.0f, -5.0f };
	Vector3 cameraTranslate{ 0.0f, 0.5f, 0.0f };
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
	
	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewportMatrix;

	

	
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

	/*	DrawSphere(pointSphere, worldViewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(closestPointSphere, worldViewProjectionMatrix, viewportMatrix, BLACK);*/


		// 各種行列の計算
	   worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
	   cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
	   viewMatrix = Inverse(cameraMatrix);
	   projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	   worldViewProjectionMatrix = Multiply(Multiply(worldMatrix, viewMatrix), projectionMatrix);
	   viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	  
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
	   //DrawGrid(worldViewProjectionMatrix, viewportMatrix);

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

	   if (IsCollision(triangle, segment))
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
	   }

	   //AABBの描画
	   if (IsCollision(aabb1, aabb2))
	   {
		   DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, RED);
	   }
	   else
	   {
		   DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, WHITE);
	   }

	   DrawAABB(aabb2, worldViewProjectionMatrix, viewportMatrix, WHITE);

		//// 描画
		//Novice::DrawTriangle(
		//	int(screenVertices[0].x), int(screenVertices[0].y),
		//	int(screenVertices[1].x), int(screenVertices[1].y),
		//	int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid
		//);

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
