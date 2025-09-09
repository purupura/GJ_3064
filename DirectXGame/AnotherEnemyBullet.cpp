#include "AnotherEnemyBullet.h"

AnotherEnemyBullet::~AnotherEnemyBullet() {
	delete sprite_;
	delete sprite2_;
}

void AnotherEnemyBullet::Initialize(Vector2 pos, Vector2 pos2) {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
	textureHandle_ = KamataEngine::TextureManager::Load("Enemy/Enemy1Bullet.png");

	sprite_ = Sprite::Create(textureHandle_, pos);

	textureHandle2_ = KamataEngine::TextureManager::Load("Enemy/Enemy1Bullet_Another.png");

	sprite2_ = Sprite::Create(textureHandle2_, pos2);

}

void AnotherEnemyBullet::Update() { Enemy1Bullet(); }

void AnotherEnemyBullet::Draw() {
	Vector4 color = {1, 1, 1, 1};
	sprite_->GetColor();
	color = {1, 1, 1, 0.2f};
	sprite_->SetColor(color);
	sprite_->Draw();
	sprite2_->Draw();
}

void AnotherEnemyBullet::Enemy1Bullet() {
	Vector2 move = {10.0, 1.0};
	switch (phase_) {

	case AnotherEnemyBullet::Phase::first:

		Vector2 pos = sprite_->GetPosition();

		if (pos.x > 20) {
			pos.x -= move.x;
		}

		sprite_->SetPosition(pos);

		// 二種類目の攻撃　仮に青とする
		Vector2 AnotherBulletPos = sprite2_->GetPosition();

		if (AnotherBulletPos.x > 20) {
			AnotherBulletPos.x -= move.x;
		}
		sprite2_->SetPosition(AnotherBulletPos);
		if (pos.x <= 30 && AnotherBulletPos.x <= 30) {
			phase_ = Phase::second; // フェイズ数に応じて % の数を変える
		}
		break;
	case AnotherEnemyBullet::Phase::second:
		pos = sprite_->GetPosition();

		if (pos.x < 1290) {
			pos.x += move.x;
		}

		// 二種類目の攻撃　仮に青とする
		AnotherBulletPos = sprite2_->GetPosition();

		if (AnotherBulletPos.x <= 30 && AnotherBulletPos.y >= 150) {
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
		if (pos.x >= 1280) {
			if (AnotherBulletPos.y <= -150 || AnotherBulletPos.y >= 400) {
				phase_ = Phase::first; // フェイズ数に応じて % の数を変える
				pos.y = 200;
				AnotherBulletPos.y = 150;
				AnotherBulletPos.x = 1290;
				isAppear_ = false;
				isDown_ = false;
			}
		}

		sprite2_->SetPosition(AnotherBulletPos);

		sprite_->SetPosition(pos);
		break;


	default:
		break;
	}
}