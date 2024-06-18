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

//delete処理
Camera::~Camera(){}

///カメラワールド行列の定義
void Camera::MakeAffineMatrix(Affine affine)
{
	cameraWorldMatrix_ = Maths::AffineMatrix(affine);
}

///ビュー行列の定義
void Camera::MakeViewMatrix() 
{
	viewMatrix_ = Maths::Inverse(cameraWorldMatrix_);
}

///プロジェクション行列の定義
void Camera::MakeProjectionMatrix() 
{
	projectionMatrix_ = Maths::MakePerspectiveFovMatrix(0.45f, kWindowWidth_ / kWindowHeight_, 0.1f, 100.0f);
}

///ビューポート行列の定義
void Camera::MakeViewportMatrix() 
{
	viewportMatrix_ = Maths::ViewportMatrix(0, 0, kWindowWidth_, kWindowHeight_, 0.0f, 1.0f);
}

///ビュー行列のゲッターの定義
Matrix4x4 Camera::GetViewMatrix() { return viewMatrix_; }

///プロジェクション行列のゲッターの定義
Matrix4x4 Camera::GetProjectionMatrix() { return projectionMatrix_; }

///ビューポート行列のゲッターの定義
Matrix4x4 Camera::GetViewportMatrix() { return viewportMatrix_; }

float Camera::GetkWindowWidth() { return kWindowWidth_; }

float Camera::GetkWindowHeight() { return kWindowHeight_; };