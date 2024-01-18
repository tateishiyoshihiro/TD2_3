#include "Stage_2.h"
#include <cassert>

void Stage_2::Initialize(Model* model) {
	
	assert(model);

	model_ = model;

	worldTransform_.Initialize();
	worldTransformBridge_.Initialize();
	worldTransformNeedleFloor_.Initialize();

	worldTransformNeedleFloor_.scale_.z = 10;

	worldTransformNeedleFloor_.scale_.x = 10;

	worldTransformNeedleFloor_.scale_.y = 5;

	worldTransformNeedleFloor_.translation_.z = 45;

	worldTransformNeedleFloor_.translation_.y = -10;

	NeedleFloorInitialize();
}

void Stage_2::Update() {

	XINPUT_STATE joyState;

	if (worldTransform_.translation_.z >= 70 && worldTransform_.translation_.z <= 80) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {

			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {

				BridgeFlag_ = true;
			}
		}
	}


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

	if (NeedleFloorFlag_ == true) {

		modelNeedleFloor_->Draw(worldTransformNeedleFloor_, viewProjection);
	}

}

void Stage_2::NeedleFloorInitialize() {

}

void Stage_2::NeedleFloorUpdate() {

	if (NeedleFloorFlag_ == false) {

		--NeedleFlame_;

		if (NeedleFlame_ <= 0) {

			NeedleFloorFlag_ = true;
		}
	}

	if (NeedleFloorFlag_ == true) {

		worldTransformNeedleFloor_.translation_.y += 1;

		if (worldTransformNeedleFloor_.translation_.y >= 10) {

			worldTransformNeedleFloor_.translation_.y = -10;

			NeedleFlame_ = 240;
			NeedleFloorFlag_ = false;
		}
	}
}
