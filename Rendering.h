#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Struct.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>

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
Matrix4x4 MakeAffineMatrix(const Vector3 &scale,const Vector3 &rotate,const Vector3 &translate);

/// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

/// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

/// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

/// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

/// ビュープロジェクション行列
Matrix4x4 MakeViewProjectionMatrix(const Matrix4x4& projectionMatrix, const Matrix4x4& viewMatrix);

void GridDraw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
