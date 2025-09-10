#include "OverScene.h"
OverScene::~OverScene() { delete overSprite_; }

void OverScene::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();

	textureHandle_ = KamataEngine::TextureManager::Load("Gameover.png");
	overSprite_ = Sprite::Create(textureHandle_, {0, 0});
}

void OverScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {
		isGameFinished_ = true;
	}
}

void OverScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());
	overSprite_->Draw();

	Sprite::PostDraw();
}