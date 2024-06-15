#include <Novice.h>
#include <Game.h>

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//Gameクラスのインスタンスを作成
	Game* game = new Game();

	//全ての処理をまとめたmain関数を呼び出す
	game->Main();

	// ライブラリの終了
	Novice::Finalize();
	delete game;
	return 0;
}
