#include "Enemy.h"
#include "worldDimensionSwitching.h"

Enemy::~Enemy() {
	delete sprite_;
	delete sprite2_;
	delete worldDimensionSwitching_;
	delete enemyBullet_;
	delete anotherEnemyBullet_;
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

	std::srand((unsigned int)std::time(nullptr));
	randam = (float)(rand() % 300); 
	anotherRandam = (float)(rand() % 300); 

	enemyBullet_ = new EnemyBullet();
	enemyBullet_->Initialize({EnemyPosition_.x + 1280, EnemyPosition_.y + randam}, {EnemyPosition_.x + 1280, EnemyPosition_.y + anotherRandam});

	anotherEnemyBullet_ = new AnotherEnemyBullet();
	anotherEnemyBullet_->Initialize({EnemyPosition_.x + 1280, EnemyPosition_.y + randam}, {EnemyPosition_.x + 1280, EnemyPosition_.y + anotherRandam});
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

		enemyBullet_->Update();
		anotherEnemyBullet_->Update();

		

		//if (anotherEnemyBullet_ && anotherEnemyBullet_->IsDead()) {
		//	delete anotherEnemyBullet_;
		//	anotherEnemyBullet_ = nullptr;
		//}
	
	}

}

void Enemy::Draw() {
	if (worldDimensionSwitching_->isWorldDimensionSwitching_ == true) {
		sprite_->Draw();

		enemyBullet_->Draw();
		
	}
	if (worldDimensionSwitching_->isWorldDimensionSwitching_ == false) {
		sprite2_->Draw();

		anotherEnemyBullet_->Draw();
		
	}


}

void Enemy::Fire() {


	
}

void Enemy::AnotherFire() {

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
