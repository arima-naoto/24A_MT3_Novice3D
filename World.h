#pragma once
#include "Maths.h"

/// <summary>
/// Mathsクラスを継承したWorldクラスを作成する
/// </summary>
class World : public Maths
{
public://メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="affine"></param>
	World(Affine affine);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~World();

	/// <summary>
	/// Affine行列
	/// </summary>
	/// <param name="affine"></param>
	void MakeAffineMatrix();

	/// <summary>
	/// ビュープロジェクション行列
	/// </summary>
	/// <param name="viewMatrix"></param>
	/// <param name="projectionMatrix"></param>
	void MakeViewProjectionMatrix(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix);


	Matrix4x4 GetViewProjectionMatrix();

private://メンバ変数

	///アフィン構造体
	Affine affine_;

	//ワールド行列
	Matrix4x4 worldMatrix_;
	
	//ワールドビュープロジェクション行列
	Matrix4x4 worldViewProjectionMatrix_;


};

