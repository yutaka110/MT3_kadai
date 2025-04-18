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
	Vector3 roate{ 0.4f,1.43f,-0.8f };

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

		//回転行列を使った計算
		Matrix4x4 roateXMatrix = MakeRoateXMatrix(roate.x);
		Matrix4x4 roateYMatrix = MakeRoateYMatrix(roate.y);
		Matrix4x4 roateZMatrix = MakeRoateZMatrix(roate.z);
		Matrix4x4 roateXYZMatrix = Multiply(roateXMatrix, Multiply(roateYMatrix, roateZMatrix));

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//行列の数値表示
		MatrixScreenPrintf(0, 0, roateXMatrix);
		MatrixScreenPrintf(0, 20 * 5, roateYMatrix);
		MatrixScreenPrintf(0, 20 * 5*2 , roateZMatrix);
		MatrixScreenPrintf(0, 20 * 5 *3, roateXYZMatrix);
		
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
