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

	Vector2 pos = sprite_->GetPosition();
	pos.x -= move.x;
	sprite_->SetPosition(pos);

	// 二種類目の攻撃　仮に青とする
	Vector2 AnotherBulletPos = sprite2_->GetPosition();
	AnotherBulletPos.x -= 5;
	sprite2_->SetPosition(AnotherBulletPos);
}