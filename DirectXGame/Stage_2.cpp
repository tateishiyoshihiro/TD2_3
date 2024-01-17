#include "Stage_2.h"
#include <cassert>

void Stage_2::Initialize(Model* model) {
	
	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	NeedleFloorInitialize();
}

void Stage_2::Update() {

	XINPUT_STATE joyState;

	if (worldTransform_.translation_.z >= 100) {

		GoalFlag_ = true;
	}

	if (GoalFlag_ == true) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {

			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {


			}
		}
	}
	
	NeedleFloorUpdate();

}

void Stage_2::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

	if (BridgeFlag_ == true) {

		modelBridge_->Draw(worldTransformBridge_, viewProjection);
	}
}

void Stage_2::NeedleFloorInitialize() {

	NeedleFlame_ = 240;

	NeedleSpeed_ = 0.5f;

}

void Stage_2::NeedleFloorUpdate() {



}
