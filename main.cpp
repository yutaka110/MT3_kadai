#include <Novice.h>
#include<cstdint>
#include"matrix4x4.h"
const char kWindowTitle[] = "LE2B_17_タケイ_ユタカ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//変数の初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	Vector3 rotate{0.0f,2.0f,0.0f};
	Vector3 translate{};
	
	// カメラの位置（Z軸マイナス方向に引いている）
	Vector3 cameraPosition{ 0.0f, 0.0f, -5.0f };

	// ローカル座標系の三角形の3頂点
	Vector3 kLocalVertices[3] = {
		{ 0.0f,  0.5f, 0.0f },  // 上
		{ 0.5f, -0.5f, 0.0f },  // 右下
		{ -0.5f, -0.5f, 0.0f }  // 左下
	};

	Vector3 v1{ 1.2f, -3.9f, 2.5f };
	Vector3 v2{ 2.8f, 0.4f, -1.3f };
	

	
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
		rotate.y += 0.02f;

		//クロス積の計算
		Vector3 cross = Cross(v1, v2);
		

		// 各種行列の計算
	   worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, translate);
	   cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
	   viewMatrix = Inverse(cameraMatrix);
	   projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	   worldViewProjectionMatrix = Multiply(Multiply(worldMatrix, viewMatrix), projectionMatrix);
	   viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		Vector3 screenVertices[3];
		for (uint32_t i = 0; i < 3; ++i) {
			Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		


		// 描画
		Novice::DrawTriangle(
			int(screenVertices[0].x), int(screenVertices[0].y),
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid
		);

		VectorScreenPrintf(0, 0, cross, "Cross");
		
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
