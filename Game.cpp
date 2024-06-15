#include "Game.h"
#include "Novice.h"

/// <summary>
/// 初期化処理
/// </summary>
Game::Game() {

#pragma region 定義しなければならない

	///ワールドアフィン
	worldAffine_ = { { 1.0f,1.0f,1.0f },{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	///カメラアフィン
	cameraAffine_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.5f,5.0f} };

	///ワールドクラスのインスタンスを作成
	world_ = new World(worldAffine_);

	///カメラクラスのインスタンスを作成
	camera_ = new Camera(cameraAffine_);

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


#pragma endregion

}

/// <summary>
/// delete処理
/// </summary>
Game::~Game(){

	///ワールド・カメラクラスを解放する
	delete world_, camera_;
}

///ウィンドウバーのタイトル
void Game::WindowTitle() 
{
	const char kWindowTitle[] = "GC2A_02_アリマ_ナオト";

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, (int)Camera::GetkWindowWidth(), (int)Camera::GetkWindowHeight());
}

///レンダリングパイプライン
void Game::MakeRendering() 
{
#pragma region レンダリングパイプラインを作成

	world_->MakeAffineMatrix(worldAffine_);

	camera_->MakeAffineMatrix(cameraAffine_);

	camera_->MakeViewMatrix();

	camera_->MakeProjectionMatrix();

	world_->MakeViewProjectionMatrix(camera_->GetViewMatrix(), camera_->GetProjectionMatrix());

	camera_->MakeViewportMatrix();

#pragma endregion

}

///移動処理
void Game::TranslateMove(char *keys) {

	//配列型ボタンキー
	char buttonKeys[4] = {
		keys[DIK_D], //Dキー
		keys[DIK_A], //Aキー
		keys[DIK_W], //Wキー
		keys[DIK_S]	 //Sキー
	};

    //複合加算演算子を使用して、ポリゴンの移動処理を行う

	//Dキーが押されている間
	if (buttonKeys[0]) 
	{
		//ポリゴンを右に動かす
		worldAffine_.translate += Vector3(-translateSpeed_.x, 0, 0);
	}

	//Aキーが押されている間
	if (buttonKeys[1]) {
		//ポリゴンを左に動かす
		worldAffine_.translate += Vector3(translateSpeed_.x, 0, 0);
	}

	//Wキーが押されている間
	if (buttonKeys[2]) 
	{
		//ポリゴンを前に動かす
		worldAffine_.translate += Vector3(0, 0, translateSpeed_.z);
	}

	//Sキーが押されている間
	if (buttonKeys[3]) 
	{
		//ポリゴンを後ろに動かす
		worldAffine_.translate += Vector3(0, 0, -translateSpeed_.z);
	}
}

///回転処理
void Game::RotateMove(){

	//ポリゴンを時計回りに回転させる
	worldAffine_.rotate += Vector3(0, rotateSpeed_, 0);
}

///更新処理(これまで定義した更新処理をUpdate関数内で呼び出す)
void Game::Update(char *keys)
{
	Maths::Update();
	Game::MakeRendering();
	Game::TranslateMove(keys);
	Game::RotateMove();
}

///ポリゴンの描画処理
void Game::DrawPolygon()
{
	//座標変換
	for (uint32_t i = 0; i < 3; ++i) {
		ndcVertex_ = Maths::Transform(kLocalVertices_[i], world_->GetViewProjectionMatrix());
		screenVertices_[i] = Maths::Transform(ndcVertex_, camera_->GetViewportMatrix());
	}

	// 三角形の法線ベクトルを計算
	Vector3 edge1 = {
		screenVertices_[1].x - screenVertices_[0].x,
		screenVertices_[1].y - screenVertices_[0].y,
		screenVertices_[1].z - screenVertices_[0].z,
	};

	Vector3 edge2 = {
		screenVertices_[2].x - screenVertices_[0].x,
		screenVertices_[2].y - screenVertices_[0].y,
		screenVertices_[2].z - screenVertices_[0].z,
	};

	Vector3 normal = Maths::Cross(edge1, edge2);

	Vector3 viewDir = { 0.0f,0.0f,1.0f };

	// DrawTriangleで座標変換済みの三角形を表示する
	// (先程の情報を使用して、表であれば描画し、裏であれば描画しない)			
	if (!Maths::RearPowerRing(normal, viewDir))
	{
		Novice::DrawTriangle(
			int(screenVertices_[0].x), int(screenVertices_[0].y), int(screenVertices_[1].x), int(screenVertices_[1].y),
			int(screenVertices_[2].x), int(screenVertices_[2].y), RED, kFillModeSolid
		);
	}

}

///描画処理(これまで定義した描画処理をDraw関数内で呼び出す)
void Game::Draw() {
	//クロス積の計算結果の描画
	Maths::Draw();
	//ポリゴンの描画
	Game::DrawPolygon();
}

void Game::Main() 
{
	Game::WindowTitle();

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///これまでの更新処理をまとめたメンバ関数Updateを呼び出す
		Game::Update(keys);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///これまでの描画処理をまとめたメンバ関数Drawを呼び出す
		Game::Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

}