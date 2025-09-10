#pragma once
#include "kamataEngine.h"
#include <assert.h>
#include <list>
#include "WorldDimensionSwitching.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "AnotherEnemyBullet.h"
using namespace KamataEngine;

class Player
{
public:
	~Player();

	void Initialize();

	void Update();

	void Draw();

	enum class Phase {  Move };

	void Fire();

	//void CheckCollision(Vector2 posA, float radiusA, Vector2 posB, float radiusB);

	static const int kFireInterval = 60; // 発射間隔


private:
	WorldTransform worldTransform_;
	DirectXCommon* dxCommon_ = nullptr;
	WorldDimensionSwitching* worldDimensionSwitching_ = nullptr;

	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;
	uint32_t textureHandle2_ = 0;
	Sprite* sprite2_ = nullptr;
	Input* input_ = nullptr;
	

	Vector2 PlayerPosition_ = { 100.0f, 300.0f };

	// 弾
	std::list<PlayerBullet*> bullets_;
	int32_t fireTimer_ = 0; // 発射タイマー

};

