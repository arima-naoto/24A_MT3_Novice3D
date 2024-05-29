#include <Novice.h>
#include "Rendering.h"
#include "imgui.h"

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

	Affine worldAffine = {
		{1.0f,1.0f,1.0f},
		{0,0,0},
		{0,0,0},
	};

	Affine cameraAffine{
		{ 1.0f,1.0f,1.0f },
		{ 0.26f,0.0f,0.0f },
		{ 0.0f,1.9f,-6.49f }
	};

	Sphere sphere = {
		{0.0f,0.0f,0.0f},
		0.5f
	};

	uint32_t color = BLACK;

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

		//ワールド行列
		Matrix4x4 worldMatrix = Rendering::MakeAffineMatrix(worldAffine);

		//カメラワールド行列
		Matrix4x4 cameraWorldMatrix = Rendering::MakeAffineMatrix(cameraAffine);
		
		//ビュー行列
		Matrix4x4 viewMatrix = Rendering::Inverse(cameraWorldMatrix);
		
		//プロジェクション行列
		Matrix4x4 projectionMatrix = Rendering::MakePerspectiveFovMatrix(0.45f, kWindowWidth / kWindowHeight, 0.1f, 100.0f);
		
		//ワールドビュープロジェクション行列
		Matrix4x4 worldViewProjectionMatrix = Rendering::Multiply(worldMatrix, Rendering::Multiply(viewMatrix, projectionMatrix));

		//ビューポート行列
		Matrix4x4 viewportMatrix = Rendering::MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight, 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//デバッグテキストの描画
		ImGui::Begin("DebugWindow");
		ImGui::DragFloat3("cameraTranslate", &cameraAffine.translate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraAffine.rotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		ImGui::End();

		//グリッド線の描画
		Rendering::GridDraw(worldViewProjectionMatrix, viewportMatrix);
		
		//球体の描画
		Rendering::DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, color);

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
