﻿#include "Rendering.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>

Matrix4x4 Rendering::Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 MultiplyMatrix{};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			MultiplyMatrix.m[i][j] = 0;
			for (int k = 0; k < 4; k++)
			{
				MultiplyMatrix.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return MultiplyMatrix;
}

#pragma region アフィン変換で使用するメンバ関数の定義

/// <summary>
/// 拡大縮小行列
/// </summary>
/// <param name="scale"></param>
/// <returns></returns>
Matrix4x4 Rendering::MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 resultScale = {
		scale.x,0.0f,0.0f,0.0f,
		0.0f,scale.y,0.0f,0.0f,
		0.0f,0.0f,scale.z,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return resultScale;
}

/// <summary>
/// X軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Rendering::MakeRotateXMatrix(float radian)
{
	Matrix4x4 rotateXMatrix = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,std::cos(radian),std::sin(radian),0.0f,
		0.0f,-std::sin(radian),std::cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateXMatrix;
}

/// <summary>
/// Y軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Rendering::MakeRotateYMatrix(float radian)
{
	Matrix4x4 rotateYMatrix = {
		std::cos(radian),0.0f,-std::sin(radian),0.0f,
		0.0f,1.0f,0.0f,0.0f,
		std::sin(radian),0.0f,std::cos(radian),0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateYMatrix;
}

/// <summary>
/// Z軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Rendering::MakeRotateZMatrix(float radian)
{
	Matrix4x4 rotateZMatrix = {
		std::cos(radian),std::sin(radian),0.0f,0.0f,
		-std::sin(radian),std::cos(radian),0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

	return rotateZMatrix;
}

/// <summary>
/// XYZ軸回転行列
/// </summary>
/// <param name="radian"></param>
/// <returns></returns>
Matrix4x4 Rendering::MakeRotateXYZMatrix(const Vector3& radian)
{
	return Multiply(MakeRotateXMatrix(radian.x), Multiply(MakeRotateYMatrix(radian.y), MakeRotateZMatrix(radian.z)));
}

/// <summary>
/// 平行移動行列
/// </summary>
/// <param name="translate"></param>
/// <returns></returns>
Matrix4x4 Rendering::MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 resultTranslate = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		translate.x,translate.y,translate.z,1.0f
	};

	return resultTranslate;
}

#pragma endregion

/// <summary>
/// アフィン変換行列
/// </summary>
/// <param name="affine"></param>
/// <returns></returns>
Matrix4x4 Rendering::MakeAffineMatrix(Affine affine) 
{
	return Multiply(Multiply(MakeScaleMatrix(affine.scale), MakeRotateXYZMatrix(affine.rotate)), MakeTranslateMatrix(affine.translate));
}



