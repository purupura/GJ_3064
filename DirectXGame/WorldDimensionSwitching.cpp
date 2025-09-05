#include "worldDimensionSwitching.h"

void WorldDimensionSwitching::Initialize() {
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	input_ = KamataEngine::Input::GetInstance();
}

void WorldDimensionSwitching::Update() {

	if (input_->TriggerKey(DIK_Z)) {
		isWorldDimensionSwitching_ = true;
	}
}
