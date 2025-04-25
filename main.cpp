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

		

		//正射影行列
		Matrix4x4 orthographicMatrix = MakeOrthographicMatrix(-160.0f, 160.f, 200.0f, 300.0f, 0.0f, 1000.0f);

		//透視投影行列
		Matrix4x4 perspectiveFovMatrix = MakePrespectiveFovMattrix(0.63f, 1.33f, 0.1f, 1000.0f);

		//ビューポート変換行列
		Matrix4x4 viewportMatrix = MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//行列の数値表示
		MatrixScreenPrintf(0, 0, orthographicMatrix);
		MatrixScreenPrintf(0, 20 * 5, perspectiveFovMatrix);
		MatrixScreenPrintf(0, 20 * 5*2 , viewportMatrix);
		
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
