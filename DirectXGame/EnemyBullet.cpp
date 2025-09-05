#include "EnemyBullet.h"

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Initialize(Vector2 pos, Vector2 pos2) {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();

	textureHandle_ = KamataEngine::TextureManager::Load("Enemy/Enemy1Bullet.png");

	sprite_ = Sprite::Create(textureHandle_, pos);
	textureHandle2_ = KamataEngine::TextureManager::Load("Enemy/Enemy1Bullet_Another.png");

	sprite2_ = Sprite::Create(textureHandle2_, pos2);
}

void EnemyBullet::Update() { Enemy1Bullet(); }

void EnemyBullet::Draw() {
	sprite_->Draw();
	sprite2_->Draw();
}

void EnemyBullet::Enemy1Bullet() {

	Vector2 move = {10.0, 1.0};
	// 一種類目の攻撃　仮に赤とする
	Vector2 normalBulletPos = sprite_->GetPosition();
	normalBulletPos.x -= move.x;
	sprite_->SetPosition(normalBulletPos);

	// 二種類目の攻撃　仮に青とする
	Vector2 AnotherBulletPos = sprite2_->GetPosition();
	AnotherBulletPos.x -= 5;
	sprite2_->SetPosition(AnotherBulletPos);
}
