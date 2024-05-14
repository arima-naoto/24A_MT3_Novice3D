#include "Camera.h"

//初期化処理
Camera::Camera(Affine affine)
{
#pragma region 定義しないといけない

	//カメラ座標
	affine_ = affine;

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
	cameraWorldMatrix_ = Rendering::MakeAffineMatrix(affine_.scale, affine_.rotate, affine_.translate);

	//ビュー行列
	viewMatrix_ = Rendering::Inverse(cameraWorldMatrix_);

	//射影行列
	projectionMatrix_ = Rendering::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth_) / float(kWindowHeight_), 0.1f, 100.0f);

	//ビューポート行列
	viewportMatrix_ = Rendering::MakeViewportMatrix(0, 0, float(kWindowWidth_), float(kWindowHeight_), 0.0f, 1.0f);
}