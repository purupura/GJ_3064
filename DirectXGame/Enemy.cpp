#include "Enemy.h"
#include "worldDimensionSwitching.h"

Enemy::~Enemy() {
	delete sprite_;
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();

	textureHandle_ = KamataEngine::TextureManager::Load("Enemy/Enemy1.png");
	sprite_ = Sprite::Create(textureHandle_, EnemyPosition_);

	textureHandle2_ = KamataEngine::TextureManager::Load("Enemy/Enemy1_Another.png");
	sprite2_ = Sprite::Create(textureHandle2_, EnemyPosition_);

	worldDimensionSwitching_ = new WorldDimensionSwitching();
	worldDimensionSwitching_->Initialize();
}

void Enemy::Update() {
	Vector2 move = {1.0, 1.0};
	EnemyPosition_ = sprite_->GetPosition();
	EnemyPosition_ = sprite2_->GetPosition();
	worldDimensionSwitching_->Update();

	switch (phase_) {
	case Enemy::Phase::Approach:
		// とりあえず左まで移動
		EnemyPosition_.x -= move.x;
		if (EnemyPosition_.x <= 300) {
			phase_ = Phase::Move;
		}
		break;
	case Enemy::Phase::Move:
		// 既定の位置に到着で行動変化　とりあえず右まで移動
		EnemyPosition_.x += move.x;
		break;
	default:
		break;
	}

	sprite_->SetPosition(EnemyPosition_);
	sprite2_->SetPosition(EnemyPosition_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
	approach();
}

void Enemy::Draw() {
	if (worldDimensionSwitching_->isWorldDimensionSwitching_ == true) {
		sprite_->Draw();
	}
	if (worldDimensionSwitching_->isWorldDimensionSwitching_ == false) {
		sprite2_->Draw();
	}

	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw();
	}
}

void Enemy::Fire() {

	EnemyBullet* newBullet_ = new EnemyBullet();

	newBullet_->Initialize(EnemyPosition_, EnemyPosition_);

	bullets_.push_back(newBullet_);
}

void Enemy::approach() {
	// 発射タイマーを減らす
	fireTimer_ -= 1;
	// 規定時間に達した
	if (fireTimer_ <= 0) {
		// 弾発射
		Fire();
		// 発射タイマーを初期化
		fireTimer_ = kFireInterval;
	}
}
