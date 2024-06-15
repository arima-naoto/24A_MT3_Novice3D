#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Struct.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>

/// <summary>
/// Renderingクラスの作成
/// </summary>
class Maths
{
public://メンバ関数の作成

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Maths();

	/// 3次元ベクトル用
	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* lebel);

	float cot(float x);

	/// 行列の積
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	/// 拡大縮小行列
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// X軸回転行列
	Matrix4x4 MakeRotateXMatrix(float radian);

	/// Y軸回転行列
	Matrix4x4 MakeRotateYMatrix(float radian);

	/// Z軸回転行列
	Matrix4x4 MakeRotateZMatrix(float radian);

	/// 回転行列
	Matrix4x4 MakeRotateMatrix(const Vector3& radian);

	/// 平行移動行列
	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// アフィン変換行列
	Matrix4x4 AffineMatrix(Affine affine);

	/// 逆行列
	Matrix4x4 Inverse(const Matrix4x4& m);

	/// 透視投影行列
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	/// ビューポート変換行列
	Matrix4x4 ViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	/// 座標変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// クロス積
	Vector3 Cross(const Vector3& v1, const Vector3& v2);

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

private://メンバ変数

	/// 3次元ベクトルメンバ変数の宣言
	Vector3 v1_;
	Vector3 v2_;
	Vector3 cross_;
};

