#include "GameScene.h"
GameScene::~GameScene() {}

void GameScene::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance(); // ★追加
	input_ = KamataEngine::Input::GetInstance();            // 使うなら初期化
	audio_ = KamataEngine::Audio::GetInstance();            // 同上
	camera_ = new Camera();                                 // ポインタなのでnewが必要（使うなら）

	textureHandle_ = KamataEngine::TextureManager::Load("backGround.png");
	backGroundSprite_ = Sprite::Create(textureHandle_, {0, 0});

	textureHandle2_ = KamataEngine::TextureManager::Load("frontFrame.png");
	frontFrameSprite_ = Sprite::Create(textureHandle2_, {0, 0});

	enemy_ = new Enemy();

	enemy_->Initialize();

	player_ = new Player();

	player_->Initialize();

	
	soundDataHandle_ = audio_->LoadWave("Audio/start.mp3");
	soundDataHandle2_ = audio_->LoadWave("Audio/BGM.mp3");

	if (!audio_->IsPlaying(seHandle_)) {
		seHandle_ = audio_->PlayWave(soundDataHandle2_, true, 1.0f);
	}


}


void GameScene::Update() {
	// ビュープロジェクションの初期化
	// camera_.Initialize();
	Cleartime_--;
	if (Cleartime_ <= 0) {
		isFinished_ = true;
		audio_->StopWave(seHandle_);
	}

	enemy_->Update();
	player_->Update();

}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	backGroundSprite_->Draw();
	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	KamataEngine::Model::PreDraw();

	/// <summary>
	/// ここにモデルの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	KamataEngine::Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	// スプライト描画後処理
	player_->Draw();
	enemy_->Draw();
	frontFrameSprite_->Draw();
	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();

#pragma endregion
}
