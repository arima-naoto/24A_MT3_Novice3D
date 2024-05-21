#include <Novice.h>
#include "Camera.h"
#include "Player.h"

const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)Camera::GetkWindowWidth(), (int)Camera::GetkWindowHeight());

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//カメラクラスのインスタンスを作成
	Affine cameraAffine = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.5f,5.0f}};
	Camera* camera = new Camera(cameraAffine);

	//Playerクラスのインスタンスを作成
	Affine playerAffine = {{ 1.0f,1.0f,1.0f },{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};
	Player* player = new Player(playerAffine);

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

		camera->Update();
		player->Update(keys, camera);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		player->Draw();

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
	delete camera, player;
	return 0;
}
