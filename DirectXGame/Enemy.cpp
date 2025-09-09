#include "Enemy.h"
#include "worldDimensionSwitching.h"

Enemy::~Enemy() {
	delete sprite_;
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
	for (AnotherEnemyBullet* anotherBullet : anotherBullets_) {
		delete anotherBullet;
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
	startTimer_--;
	sprite_->SetPosition(EnemyPosition_);
	sprite2_->SetPosition(EnemyPosition_);
	if (startTimer_ < 0) {

		switch (phase_) {
		case Enemy::Phase::Approach:
			// 攻撃動作
			approach();
			break;
		case Enemy::Phase::Move:
			// 既定の位置に到着で行動変化　とりあえず右まで移動
			EnemyPosition_.x += move.x;
			break;
		default:
			break;
		}



		for (EnemyBullet* bullet : bullets_) {
			bullet->Update();
	}

		for (AnotherEnemyBullet* anotherBullet : anotherBullets_) {
			anotherBullet->Update();
		}
	}

}

void Enemy::Draw() {
	if (worldDimensionSwitching_->isWorldDimensionSwitching_ == true) {
		sprite_->Draw();
		for (EnemyBullet* bullet : bullets_) {
			bullet->Draw();
		}
	}
	if (worldDimensionSwitching_->isWorldDimensionSwitching_ == false) {
		sprite2_->Draw();
		for (AnotherEnemyBullet* anotherBullet : anotherBullets_) {
			anotherBullet->Draw();
		}
	}


}

void Enemy::Fire() {

	EnemyBullet* newBullet_ = new EnemyBullet();

	newBullet_->Initialize({EnemyPosition_.x + 1280, EnemyPosition_.y}, {EnemyPosition_.x + 1280, EnemyPosition_.y});

	bullets_.push_back(newBullet_);

	
}

void Enemy::AnotherFire() {
	AnotherEnemyBullet* newAnotherBullet_ = new AnotherEnemyBullet();

	newAnotherBullet_->Initialize({EnemyPosition_.x + 1280, EnemyPosition_.y}, {EnemyPosition_.x + 1280, EnemyPosition_.y});

	anotherBullets_.push_back(newAnotherBullet_);
}

void Enemy::approach() {

		// 発射タイマーを減らす
		fireTimer_ -= 1;
		// 規定時間に達した
		if (fireTimer_ <= 0) {
			// 弾発射
			Fire();
		    AnotherFire();
			// 発射タイマーを初期化
			fireTimer_ = kFireInterval;
		}


}

void Enemy::AnotherApproach() {

		// 発射タイマーを減らす
		fireTimer_ -= 1;
		// 規定時間に達した
		if (fireTimer_ <= 0) {
			// 弾発射
		
			// 発射タイマーを初期化
			fireTimer_ = kFireInterval;
		}
	
}
