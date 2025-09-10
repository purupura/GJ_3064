#pragma once
#include "EnemyBullet.h"
#include "AnotherEnemyBullet.h"
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
	void AnotherFire();

	static const int kFireInterval = 60; // 発射間隔

	void approach();
	void AnotherApproach();

	bool IsDead() const { return isDead_; }

	void OnHit();

	Vector2 GetPosition() { return EnemyPosition_; }
    float GetRadius() { return 32.0f; }

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

	Vector2 EnemyPosition_ = {0.0f, 0.0f};


	EnemyBullet* enemyBullet_ = nullptr;	
	AnotherEnemyBullet* anotherEnemyBullet_ = nullptr;
	float randam = 0;
	float anotherRandam = 0;

	int32_t fireTimer_ = 0; // 発射タイマー
	int32_t startTimer_ = 60*2; // タイマー

	int hp_ = 0;
	bool isDead_ = false;
};