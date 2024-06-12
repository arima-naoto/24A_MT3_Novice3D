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

	//ワールドマトリックス
	worldMatrix_ = {};

	//ワールドビュープロジェクション
	worldViewProjectionMatrix_ = {};

#pragma endregion
}

void Player::Translate(char*keys)
{
#pragma region キー入力処理

	//ボタンキーの配列型変数を用意
	char bottomKeys[4] = {
		keys[DIK_D], //Dキー
		keys[DIK_A], //Aキー
		keys[DIK_W], //Wキー
		keys[DIK_S]  //Sキー
	};

	if (bottomKeys[0])//Dキーが押されている間
	{
		//三角形を右に動かす
		affine_.translate -= Vector3(translateSpeed_.x, 0, 0);
	}

	if (bottomKeys[1])//Aキーが押されている間
	{
		//三角形を左に動かす
		affine_.translate += Vector3(translateSpeed_.x, 0, 0);
	}

	if (bottomKeys[2])//Wキーが押されている間 
	{
		//三角形を前に動かす
		affine_.translate += Vector3(0, 0, translateSpeed_.z);
	}

	if (bottomKeys[3])//Sキーが押されている間 
	{
		//三角形を後ろに動かす
		affine_.translate -= Vector3(0, 0, translateSpeed_.z);
	}

#pragma endregion
}

void Player::Rotate()
{
	//Y軸を中心に回転させる
	affine_.rotate += Vector3(0, rotateSpeed_, 0);
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
	
	//DrawTriangleで座標変換済みの三角形を表示する
	Novice::DrawTriangle(
		int(screenVertices_[0].x), int(screenVertices_[0].y), int(screenVertices_[1].x), int(screenVertices_[1].y),
		int(screenVertices_[2].x), int(screenVertices_[2].y), RED, kFillModeSolid
	);
}
