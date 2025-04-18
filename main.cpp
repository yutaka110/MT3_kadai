#include <Novice.h>
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
	Vector3 translate{ 4.1f,2.6f,0.8f };

	Vector3 scale{ 1.5f,5.2f,7.3f };

	Vector3 point{ 2.3f,3.8f,1.4f };

	Matrix4x4 transformMatrix =
	{
	   1.0f,2.0f,3.0f,4.0f,
	   3.0f,1.0f,1.0f,2.0f,
	   1.0f,4.0f,2.0f,3.0f,
	   2.0f,2.0f,1.0f,3.0f
	};

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

		//座標返還
		Vector3 transform = Transform(point, transformMatrix);

		//平行移動行列を使った計算
		Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

		//拡大縮小行列を使った計算
		Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//ベクトル,行列の数値表示
		VectorScreenPrintf(0, 0, transform,"transformed");
		MatrixScreenPrintf(0, 20*5, translateMatrix);
		MatrixScreenPrintf(0, 20 * 5*2 , scaleMatrix);

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
