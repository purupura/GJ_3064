#include "EnemyBullet.h"



EnemyBullet::~EnemyBullet() {
	delete sprite_;
	delete sprite2_;
}

void EnemyBullet::Initialize(Vector2 pos, Vector2 pos2) {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();

	textureHandle_ = KamataEngine::TextureManager::Load("Enemy/Enemy1Bullet.png");

	sprite_ = Sprite::Create(textureHandle_, pos);

	textureHandle2_ = KamataEngine::TextureManager::Load("Enemy/Enemy1Bullet_Another.png");

	sprite2_ = Sprite::Create(textureHandle2_, pos2);

	   std::srand((unsigned int)std::time(nullptr));

}

void EnemyBullet::Update() { Enemy1Bullet(); }

void EnemyBullet::Draw() {
	Vector4 color = {1, 1, 1, 1};
	sprite2_->GetColor();
	color = {1, 1, 1, 0.2f};
	sprite2_->SetColor(color);

	sprite2_->Draw();
	sprite_->Draw();
}

void EnemyBullet::Enemy1Bullet() {
	Vector2 move = {10.0, 1.0};
	switch (phase_) {
	
	case EnemyBullet::Phase::first:

		posi = sprite_->GetPosition();
		
		if (posi.x > 20) {
			posi.x -= move.x;
		}
		
		sprite_->SetPosition(posi);

		// 二種類目の攻撃　仮に青とする
		AnotherBulletPos = sprite2_->GetPosition();
	
		if (AnotherBulletPos.x > 20) {
			AnotherBulletPos.x -= move.x;
		}
		sprite2_->SetPosition(AnotherBulletPos);
		if (posi.x <= 30 && AnotherBulletPos.x <= 30) {

			phase_ = Phase::second;; // フェイズ数に応じて % の数を変える
		}
		break;
	case EnemyBullet::Phase::second:
		posi = sprite_->GetPosition();

	if (posi.x < 1290) {
			posi.x += move.x;
		}

		// 二種類目の攻撃　仮に青とする
		AnotherBulletPos = sprite2_->GetPosition();

		if (AnotherBulletPos.x <= 30 && AnotherBulletPos.y>=150) {
			if (isDown_ == false) {
				isAppear_ = true;
			}
		}
		if (isAppear_) {
			AnotherBulletPos.y -= move.y;
		}

		if (AnotherBulletPos.x <= 30 && AnotherBulletPos.y < 150) {
			if (isAppear_ == false) {
				isDown_ = true;
			}
		}
		if (isDown_) {
			AnotherBulletPos.y += move.y;
		}
		if (posi.x >= 1280) {
			if (AnotherBulletPos.y <= -150 || AnotherBulletPos.y >= 400) {
				phase_ = Phase::first; // フェイズ数に応じて % の数を変える
				posi.y = 200;
				AnotherBulletPos.y = 150;
				AnotherBulletPos.x = 1290;
				isAppear_ = false;
				isDown_ = false;
			}
		
		}

		sprite2_->SetPosition(AnotherBulletPos);

		sprite_->SetPosition(posi);
		break;

	default:
		break;
	}


}

bool EnemyBullet::CheckCollision(Vector2 playerPos, float playerRadius) { 
	
	  // 弾の当たり判定用座標（sprite_とsprite2_の両方を確認）
	Vector2 bulletPos1 = sprite_->GetPosition();
	Vector2 bulletPos2 = sprite2_->GetPosition();

	float bulletRadius = 16.0f; // 弾の大きさに応じて調整

	// プレイヤーとの距離をチェック
	auto isHit = [&](Vector2 bulletPos) {
		float dx = playerPos.x - bulletPos.x;
		float dy = playerPos.y - bulletPos.y;
		float distSq = dx * dx + dy * dy;
		float radiusSum = playerRadius + bulletRadius;
		return distSq <= radiusSum * radiusSum;
	};

	// どちらかの弾が当たれば true
	return (isHit(bulletPos1) || isHit(bulletPos2));
 }

