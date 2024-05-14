#pragma once
#include "Rendering.h"

#pragma region Renderingクラスを継承したCameraクラスを宣言

class Camera : public Rendering
{
public://メンバ関数

	//コンストラクタ
	Camera();

	//更新処理
	void Update();

public://Cameraクラスのメンバ変数のカプセル化

	//ビュー行列のゲッター
	Matrix4x4 GetViewMatrix() { return viewMatrix_; };

	//射影行列のゲッター
	Matrix4x4 GetProjectionMatrix() { return projectionMatrix_; };

	//ビューポート行列のゲッター
	Matrix4x4 GetViewportMatrix() { return viewportMatrix_; };

private://メンバ変数

	//カメラ座標
	Vector3 cameraPosition;

	//カメラワールド行列
	Matrix4x4 cameraWorldMatrix_;
	
	//ビュー行列
	Matrix4x4 viewMatrix_;
	
	//射影行列
	Matrix4x4 projectionMatrix_;
	
	//ビューポート行列
	Matrix4x4 viewportMatrix_;

};

#pragma endregion