#pragma once
#include "kamataEngine.h"

using namespace KamataEngine;

class WorldDimensionSwitching {
public:
	void Initialize();
	void Update();

	bool isWorldDimensionSwitching_ = false;

private:
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
};
