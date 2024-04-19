#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

/// <summary>
/// Affine構造体の作成
/// </summary>
struct Affine {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

/// <summary>
/// Renderingクラスの作成
/// </summary>
class Rendering
{
public://メンバ関数の作成

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Rendering();

#pragma region //数値表示用メンバ関数の作成

	/// <summary>
	/// 3次元ベクトル用
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="vector"></param>
	/// <param name="lebel"></param>
	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* lebel);

	/// <summary>
	/// 4x4行列用
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="matrix"></param>
	/// <param name="label"></param>
	void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

#pragma endregion

#pragma region 4x4行列メンバ関数の作成

	/// <summary>
	/// 行列の積
	/// </summary>
	/// <param name="m1"></param>
	/// <param name="m2"></param>
	/// <returns></returns>
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	/// <summary>
	/// 拡大縮小行列
	/// </summary>
	/// <param name="scale"></param>
	/// <returns></returns>
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	/// <summary>
	/// X軸回転行列
	/// </summary>
	/// <param name="radian"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateXMatrix(float radian);

	/// <summary>
	/// Y軸回転行列
	/// </summary>
	/// <param name="radian"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateYMatrix(float radian);

	/// <summary>
	/// Z軸回転行列
	/// </summary>
	/// <param name="radian"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateZMatrix(float radian);

	/// <summary>
	/// XYZ軸回転行列
	/// </summary>
	/// <param name="radian"></param>
	/// <returns></returns>
	Matrix4x4 MakeRotateXYZMatrix(const Vector3& radian);

	/// <summary>
	/// 平行移動行列
	/// </summary>
	/// <param name="translate"></param>
	/// <returns></returns>
	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	/// <summary>
	/// アフィン変換行列
	/// </summary>
	/// <param name="affine"></param>
	/// <returns></returns>
	Matrix4x4 MakeAffineMatrix(Affine affine);

	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Matrix4x4 Inverse(const Matrix4x4& matrix);

	/// <summary>
	/// 透視投影行列
	/// </summary>
	/// <param name="fovY"></param>
	/// <param name="aspectRatio"></param>
	/// <param name="nearClip"></param>
	/// <param name="farClip"></param>
	/// <returns></returns>
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	/// <summary>
	/// ビューポート変換行列
	/// </summary>
	/// <param name="left"></param>
	/// <param name="top"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="minDepth"></param>
	/// <param name="maxDepth"></param>
	/// <returns></returns>
	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

#pragma endregion

	/// <summary>
	/// 座標変換
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

public://メンバ変数

	/// <summary>
	/// Affine構造体メンバ変数の宣言
	/// </summary>
	Affine world_;
	Affine camera_;

	/// <summary>
	/// 3次元ベクトルメンバ変数の宣言
	/// </summary>
	Vector3 v1_;
	Vector3 v2_;
	Vector3 cross_;
	Vector3 screenVertices_[3];
	Vector3 ndcVertex_;

	/// <summary>
	/// 4x4行列メンバ変数の宣言
	/// </summary>
	Matrix4x4 worldMatrix_;
	Matrix4x4 cameraMatrix_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;
	Matrix4x4 viewportMatrix_;

};

