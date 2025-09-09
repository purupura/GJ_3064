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