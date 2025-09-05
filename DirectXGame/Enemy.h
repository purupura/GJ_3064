#pragma once
#include "EnemyBullet.h"
#include "WorldDimensionSwitching.h"
#include "kamataEngine.h"
#include <assert.h>
#include <list>

using namespace KamataEngine;

class Enemy {
public:
	~Enemy();

	void Initialize();

	void Update();

	void Draw();

	enum class Phase { Approach, Move };

	void Fire();

	static const int kFireInterval = 60; // 発射間隔

	void approach();

private:
	WorldTransform worldTransform_;
	DirectXCommon* dxCommon_ = nullptr;
	WorldDimensionSwitching* worldDimensionSwitching_ = nullptr;

	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;
	uint32_t textureHandle2_ = 0;
	Sprite* sprite2_ = nullptr;

	Input* input_ = nullptr;

	Phase phase_ = Phase::Approach;

	Vector2 EnemyPosition_ = {1280.0f, 300.0f};

	// 弾
	std::list<EnemyBullet*> bullets_;

	int32_t fireTimer_ = 0; // 発射タイマー
};
