#pragma once
#include "Maths.h"
#include "World.h"
#include "Camera.h"

/// <summary>
/// Mathsクラスを継承したGameクラスを作成する
/// </summary>
class Game : public Maths
{
public://メンバ関数

	/// コンストラクタ
	Game();

	/// デストラクタ
	~Game();

	///ウィンドウバーのタイトル
	void WindowTitle();

	/// レンダリングパイプライン
	void MakeRendering();

	///移動処理
	void TranslateMove(char *keys);

	///回転処理
	void RotateMove();

	///更新処理
	void Update(char* Keys);

	///ポリゴンの描画
	void DrawPolygon();

	///描画処理
	void Draw();

	///	処理をまとめるメンバ関数
	void Main();

private://メンバ変数

	///アフィン構造体
	Affine worldAffine_;
	Affine cameraAffine_;

	///ワールドクラス
	World* world_;

	///カメラクラス
	Camera* camera_;

	///NDC頂点
	Vector3 ndcVertex_;

	///移動速度
	Vector3 translateSpeed_;

	///回転速度
	float rotateSpeed_;

	//三角形のローカル頂点
	Vector3 kLocalVertices_[3];

	//三角形のスクリーン頂点
	Vector3 screenVertices_[3];


};

