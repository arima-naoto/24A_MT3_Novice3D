#include "World.h"

World::World(Affine affine)
{
#pragma region 定義しなければならない

	//アフィン構造体
	affine_ = affine;

	//ワールド行列
	worldMatrix_ = {};

	//ワールドビュープロジェクション行列
	worldViewProjectionMatrix_ = {};
}

World::~World(){}

/// <summary>
/// ワールド行列を作成する
/// </summary>
/// <param name="affine"></param>
void World::MakeAffineMatrix(Affine affine)
{
	worldMatrix_ = Maths::AffineMatrix(affine);
}

/// <summary>
/// ワールドビュープロジェクション行列を定義する
/// </summary>
/// <param name="viewMatrix"></param>
/// <param name="projectionMatrix"></param>
void World::MakeViewProjectionMatrix(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix) 
{
	worldViewProjectionMatrix_ = Maths::Multiply(worldMatrix_, Maths::Multiply(viewMatrix, projectionMatrix));
}

/// <summary>
/// ビュープロジェクション行列ゲッターの定義
/// </summary>
/// <returns></returns>
Matrix4x4 World::GetViewProjectionMatrix() { return worldViewProjectionMatrix_; }

