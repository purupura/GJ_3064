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

private:
	WorldTransform worldTransform_;
	DirectXCommon* dxCommon_ = nullptr;

	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;
	uint32_t textureHandle2_ = 0;
	Sprite* sprite2_ = nullptr;

	Input* input_ = nullptr;
};
