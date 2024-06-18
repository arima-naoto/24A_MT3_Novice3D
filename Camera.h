#pragma once
#include "Maths.h"
#include "Struct.h"

#pragma region Renderingクラスを継承したCameraクラスを宣言

class Camera : public Maths
{
public://メンバ関数

	//コンストラクタ
	Camera(Affine affine);

	///デストラクタ
	~Camera();

	/// <summary>
	/// アフィン行列
	/// </summary>
	/// <param name="affine"></param>
	void MakeAffineMatrix(Affine affine);

	/// <summary>
	/// ビュー行列
	/// </summary>
	/// <param name="v"></param>
	void MakeViewMatrix();

	/// <summary>
	/// プロジェクション行列
	/// </summary>
	void MakeProjectionMatrix();

	/// <summary>
	/// ビューポート行列
	/// </summary>
	void MakeViewportMatrix();

public://Cameraクラスのメンバ変数のカプセル化

	//ビュー行列のゲッター
	Matrix4x4 GetViewMatrix();

	//射影行列のゲッター
	Matrix4x4 GetProjectionMatrix();

	//ビューポート行列のゲッター
	Matrix4x4 GetViewportMatrix();

	static float GetkWindowWidth();

	static float GetkWindowHeight();

private://メンバ変数

	//画面横幅
	static inline const float kWindowWidth_ = 1280.0f;

	//画面縦幅
	static inline const float kWindowHeight_ = 720.0f;

	//アフィン構造体
	Affine affine_;

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