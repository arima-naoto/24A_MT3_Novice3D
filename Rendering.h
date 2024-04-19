#pragma once
#include "Matrix4x4.h"

/// <summary>
/// Renderingクラスを作成する
/// </summary>
class Rendering
{
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Rendering();

	/// <summary>
	/// 演算結果の数値表示
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="matrix"></param>
	/// <param name="label"></param>
	void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

#pragma region //4x4行列関数の作成

	/// <summary>
	/// 投資投影行列
	/// </summary>
	/// <param name="perspective"></param>
	/// <returns></returns>
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	/// <summary>
	/// 正射影行列
	/// </summary>
	/// <param name="point"></param>
	/// <returns></returns>
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

	/// <summary>
	/// ビューポート変換行列
	/// </summary>
	/// <param name="viewport"></param>
	/// <returns></returns>
	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	void Update();

	void Draw();

#pragma endregion

public://メンバ変数

	Matrix4x4 orthographicMatrix_;

	Matrix4x4 perspectiveFovMatrix_;

	Matrix4x4 viewportMatrix_;

};

