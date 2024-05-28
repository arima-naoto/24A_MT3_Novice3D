#include <Novice.h>
#include "Rendering.h"

const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";
static inline const float kWindowWidth = 1280.0f;
static inline const float kWindowHeight = 720.0f;



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)kWindowWidth, (int)kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	Vector3 cameraScale{ 1.0f,1.0f,1.0f };

	Sphere sphere = {
		{0.0f,0.0f,0.0f},
		0.5f
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

		//カメラワールド行列
		Matrix4x4 cameraWorldMatrix = MakeAffineMatrix(cameraScale,cameraRotate,cameraTranslate);
		
		//ビュー行列
		Matrix4x4 viewMatrix = Inverse(cameraWorldMatrix);
		
		//プロジェクション行列
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, kWindowWidth / kWindowHeight, 0.1f, 100.0f);
		
		//ビューポート行列
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight, 0.0f, 1.0f);

		//ビューポート行列
		Matrix4x4 viewprojectionMatrix = MakeViewProjectionMatrix(projectionMatrix, viewMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		GridDraw(viewprojectionMatrix, viewportMatrix);

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
