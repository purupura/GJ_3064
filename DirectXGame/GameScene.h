#pragma once
#include "Enemy.h"
#include "KamataEngine.h"
#include "WorldDimensionSwitching.h"

using namespace KamataEngine;

class GameScene {
public:
	/// <summary>
	/// デストクラタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsFinished() const { return isFinished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Camera* camera_ = nullptr;
	Enemy* enemy_ = nullptr;

	uint32_t textureHandle_ = 0;
	Sprite* TestSprite_ = nullptr;
	bool isFinished_ = false;

	//音楽
	uint32_t soundDataHandle_ = 0;
	uint32_t soundDataHandle2_ = 0;
	uint32_t playSoundId_ = 0;
	uint32_t playSoundId2_ = 0;
	bool isBGMPlay_ = false;
	bool isBGMPlay2_ = false;
	
};
