#pragma once
#include "Rendering.h"
#include "Camera.h"
#include "Novice.h"

class World : public Rendering
{
public:

	World(Affine affine,Sphere sphere);

	void Update(Camera *camera);

	void DrawGrid(const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix);

	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

public:

	Matrix4x4 GetViewProjectionMatrix() { return worldViewProjectionMatrix_; };

private:

	Affine affine_;

	Sphere sphere_;

	Matrix4x4 worldMatrix_;

	Matrix4x4 worldViewProjectionMatrix_;
};

