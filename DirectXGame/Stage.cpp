#include "Stage.h"
#include <cassert>

void Stage::Initialize(Model* model) {
	
	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.rotation_.y = 90.0f;

	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};
}

void Stage::Update() { 

	//XINPUT_STATE joyState;
	
	/*if (worldTransform_.translation_.z >= 100) {

		GoalFlag_ = true;
	}

	if (GoalFlag_ == true) {

		if (Input::GetInstance()->GetJoystickState(0,joyState)) {

			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {

				GoalFlag_ = false;
			}
		}
	}*/

	worldTransform_.TransferMatrix(); 
}

void Stage::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}
