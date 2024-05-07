#include "Camera.h"

//画面横幅
static const float kWindowWidth = 1280;

//画面縦幅
static const float kWindowHeight = 720;

//初期化処理
Camera::Camera()
{
#pragma region 定義しないといけない

	//カメラ座標
	cameraPosition = { 0.0f,0.5f,5.0f };

	//カメラワールド行列
	cameraWorldMatrix_ = {};

	//ビュー行列
	viewMatrix_ = {};

	//射影行列
	projectionMatrix_ = {};

	//ビューポート行列
	viewportMatrix_ = {};

#pragma endregion
}

//更新処理
void Camera::Update()
{
	//アフィン変換
	cameraWorldMatrix_ = Rendering::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);

	//ビュー行列
	viewMatrix_ = Rendering::Inverse(cameraWorldMatrix_);

	//射影行列
	projectionMatrix_ = Rendering::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

	//ビューポート行列
	viewportMatrix_ = Rendering::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
}