#pragma once
#include "Maths.h"

/// <summary>
/// Mathsクラスを継承したCameraクラスを作成
/// </summary>
class Camera : public Maths
{
public://メンバ関数

	/// <summary>
	/// インストラクタ
	/// </summary>
	/// <param name="affine">アフィン構造体</param>
	Camera(Affine affine);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Camera();

	/// <summary>
	/// アフィン行列
	/// </summary>
	/// <param name="affine">アフィン構造体</param>
	void MakeAffineMatrix(Affine affine);

	/// <summary>
	/// ビュー行列
	/// </summary>
	void MakeViewMatrix();

	/// <summary>
	/// プロジェクション行列
	/// </summary>
	void MakeProjectionMatrix();

	/// <summary>
	/// ビューポート行列
	/// </summary>
	void MakeViewportMatrix();

public://メンバ変数のゲッター

	//ビュー行列のゲッター
	Matrix4x4 GetViewMatrix();
	
	//プロジェクション行列のゲッター
	Matrix4x4 GetProjectionMatrix();

	//ビューポート行列のゲッター
	Matrix4x4 GetViewportMatrix();

	//画面横幅のゲッター
	float GetKWindowWidth();

	//画面縦幅のゲッター
	float GetKWindowHeight();

private://メンバ変数

	//アフィン構造体
	Affine affine_;

	//カメラワールド行列
	Matrix4x4 cameraWorldMatrix_;

	//ビュー行列
	Matrix4x4 viewMatrix_;

	//プロジェクション行列
	Matrix4x4 projectionMatrix_;

	//ビューポート行列
	Matrix4x4 viewportMatrix_;

	//画面横幅
	float kWindowWidth_;

	//画面縦幅
	float kWindowHeight_;

};

