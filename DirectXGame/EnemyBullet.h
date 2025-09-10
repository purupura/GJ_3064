#pragma once
#include "kamataEngine.h"
#include <assert.h>

using namespace KamataEngine;

class EnemyBullet {

public:
	~EnemyBullet();

	void Initialize(Vector2 pos, Vector2 pos2);

	void Update();

	void Draw();

	void Enemy1Bullet();

	enum class Phase { first, second,therd };

	// 位置を返す関数を追加
	Vector2 GetPosition() const { return sprite_->GetPosition(); }
	Vector2 GetAnotherPosition() const { return sprite2_->GetPosition(); }

	// もしくは弾の当たり判定用の矩形を返す
	Vector2 GetSize() const { return {1280.0f, 100.0f}; }

	Vector2 posi = {0, 0};
	Vector2 AnotherBulletPos = {0, 0};

	bool CheckCollision(Vector2 playerPos, float playerRadius);

private:
	WorldTransform worldTransform_;
	DirectXCommon* dxCommon_ = nullptr;

	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;
	uint32_t textureHandle2_ = 0;
	Sprite* sprite2_ = nullptr;
	Phase phase_ = Phase::first;

	Input* input_ = nullptr;
	bool isAppear_ = false;
	bool isDown_ = false;

};