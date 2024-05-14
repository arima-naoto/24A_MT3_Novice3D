#pragma once
#include "Rendering.h"
#include "Camera.h"
#include "Struct.h"

#pragma region Renderingクラスを継承したPlayerクラスを作成

class Player : public Rendering
{
public:// メンバ関数

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player(Affine affine);
	
	/// <summary>
	/// キー入力移動処理
	/// </summary>
	/// <param name="keys"></param>
	void Translate(char* keys);

	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotate();
	
	/// <summary>
	/// ポリゴンが動く処理
	/// </summary>
	void Move(char *keys);

	//更新処理
	void Update(char *keys,Camera * camera);

	//描画処理
	void Draw();

private:// メンバ変数

	Affine affine_;
	
	//NDC頂点
	Vector3 ndcVertex_;
	
	//移動速度
	Vector3 translateSpeed_;
	
	//回転速度
	float rotateSpeed_;
	
	//三角形のローカル頂点
	Vector3 kLocalVertices_[3];
	
	//三角形のスクリーン頂点
	Vector3 screenVertices_[3];
	
	//ワールドマトリックス
	Matrix4x4 worldMatrix_;
	
	//ワールドビュープロジェクション行列
	Matrix4x4 worldViewProjectionMatrix_;

};

#pragma endregion
