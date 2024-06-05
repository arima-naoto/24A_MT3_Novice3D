#include "Player.h"
#include "Novice.h"
#define _USE_MATH_DEFINES
#include "cmath"

Player::Player(Affine affine)
{
#pragma region 定義しなければならない

	affine_ = affine;

	//NDC頂点
	ndcVertex_ = {};

	//移動速度
	translateSpeed_ = {
		1.0f / 50.0f,
		0.0f,
		1.0f / 40.0f
	};

	//回転速度
	rotateSpeed_ = 1.0f / 30.0f;

	//三角形の頂点(ローカル)
	kLocalVertices_[0] = { 0,0,0 };
	kLocalVertices_[1] = { -0.5f,1,0 };
	kLocalVertices_[2] = { 0.5f,1,0 };

	//三角形の頂点(スクリーン)
	for (uint32_t i = 0; i < 3; i++) {
		screenVertices_[i] = {};
	}

	worldMatrix_ = {};

	worldViewProjectionMatrix_ = {};

#pragma endregion
}

void Player::Translate(char*keys)
{
#pragma region キー入力処理

	if (keys[DIK_D])//Dキーが押されている間
	{
		//三角形を右に動かす
		affine_.translate.x -= translateSpeed_.x;
	}

	if (keys[DIK_A])//Aキーが押されている間
	{
		//三角形を左に動かす
		affine_.translate.x += translateSpeed_.x;
	}

	if (keys[DIK_W])//Wキーが押されている間 
	{
		//三角形を前に動かす
		affine_.translate.z += translateSpeed_.z;
	}

	if (keys[DIK_S])//Sキーが押されている間 
	{
		//三角形を後ろに動かす
		affine_.translate.z -= translateSpeed_.z;
	}

#pragma endregion
}

void Player::Rotate()
{
	//Y軸を中心に回転させる
	affine_.rotate.y += rotateSpeed_;
}

void Player::Move(char *keys)
{
	Player::Translate(keys);
	Player::Rotate();
}

void Player::Update(char *keys,Camera * camera)
{
	//クロス積の演算処理
	Maths::Update();

	//ポリゴンの移動処理
	Player::Move(keys);

	//ワールド行列
	worldMatrix_ = Maths::MakeAffineMatrix(affine_.scale, affine_.rotate, affine_.translate);
	
	//ワールドビュープロジェクション行列
	worldViewProjectionMatrix_ = Maths::Multiply(worldMatrix_, Maths::Multiply(camera->GetViewMatrix(), camera->GetProjectionMatrix()));

	//座標変換
	for (uint32_t i = 0; i < 3; ++i) {
		ndcVertex_ = Maths::Transform(kLocalVertices_[i], worldViewProjectionMatrix_);
		screenVertices_[i] = Maths::Transform(ndcVertex_, camera->GetViewportMatrix());
	}
}

void Player::Draw()
{
	//クロス積の計算結果を表示
	Maths::Draw();
	
	// 三角形の法線ベクトルを計算
	Vector3 edge1 = screenVertices_[1] - screenVertices_[0];

	Vector3 edge2 = screenVertices_[2] - screenVertices_[0];

	Vector3 normal = Maths::Cross(edge1, edge2);

	Vector3 viewDir = { 0.0f,0.0f,1.0f };

	//DrawTriangleで座標変換済みの三角形を表示する、ただし先程の情報を使用して、表であれば描画し、裏であれば表示しない			
	if (!Maths::RearPowerRing(normal, viewDir)) 
	{
		Novice::DrawTriangle(
			int(screenVertices_[0].x), int(screenVertices_[0].y), int(screenVertices_[1].x), int(screenVertices_[1].y),
			int(screenVertices_[2].x), int(screenVertices_[2].y), RED, kFillModeSolid
		);
	}
}
