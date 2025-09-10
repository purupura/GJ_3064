#include "Player.h"
#include "worldDimensionSwitching.h"

Player::~Player() {
	delete sprite_;
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	textureHandle_ = KamataEngine::TextureManager::Load("Player/Player1.png");
	sprite_ = Sprite::Create(textureHandle_, PlayerPosition_);
	textureHandle2_ = KamataEngine::TextureManager::Load("Player/Player1_Another.png");
	sprite2_ = Sprite::Create(textureHandle2_, PlayerPosition_);
	worldDimensionSwitching_ = new WorldDimensionSwitching();
	worldDimensionSwitching_->Initialize();
}

void Player::Update() {
	
	 // 入力処理 (WASDで移動)
    const float speed = 5.0f;  // 移動速度（調整可）
    if (input_->PushKey(DIK_W)) {
        PlayerPosition_.y -= speed;  // 上
    }
    if (input_->PushKey(DIK_S)) {
        PlayerPosition_.y += speed;  // 下
    }
    if (input_->PushKey(DIK_A)) {
        PlayerPosition_.x -= speed;  // 左
    }
    if (input_->PushKey(DIK_D)) {
        PlayerPosition_.x += speed;  // 右
    }

	sprite_->SetPosition(PlayerPosition_);
	sprite2_->SetPosition(PlayerPosition_);
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	
	}
	
	approach();
}

void Player::Draw() {
	if (worldDimensionSwitching_->isWorldDimensionSwitching_ == true) {
		sprite_->Draw();
	}
	if (worldDimensionSwitching_->isWorldDimensionSwitching_ == false) {
		sprite2_->Draw();
	}
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw();
	}
}

void Player::Fire() {
	// 発射間隔の調整

	if (fireTimer_ > 0) {
		return;
	}
	Vector2 bulletPos = sprite_->GetPosition();
	Vector2 bulletPos2 = sprite2_->GetPosition();
	bulletPos.x += 50.0f; // 弾の出現位置を調整
	bulletPos2.x += 50.0f;
	PlayerBullet* newBullet = new PlayerBullet();
	newBullet->Initialize(bulletPos, bulletPos2);
	bullets_.push_back(newBullet);
	fireTimer_ = kFireInterval;
}

void Player::approach() {
	// 発射タイマーを減らす
	fireTimer_ -= 1;
	if (fireTimer_ <= 0) {
		// 弾発射
		Fire();
		// 発射タイマーを初期化
		fireTimer_ = kFireInterval;
	}
}