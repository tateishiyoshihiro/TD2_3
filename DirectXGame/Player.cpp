#include "Player.h"
#include "assert.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "ImGuiManager.h"

void Player::Initalize(const std::vector<Model*>& models) {

	   BaseCharacter::Initalize(models);

	// 親子関係の設定
	worldTransform_[1].parent_ = &worldTransform_[0];
	worldTransform_[2].parent_ = &worldTransform_[0];
	worldTransform_[3].parent_ = &worldTransform_[0];

	

	worldTransform_[0].scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_[0].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[0].translation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_[1].scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_[1].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[1].translation_ = {0.0f, 1.57f, 0.0f};

	worldTransform_[2].scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_[2].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[2].translation_ = {-0.51f, 1.26f, 0.0f};

	worldTransform_[3].scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_[3].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[3].translation_ = {0.51f, 1.26f, 0.0f};

	for (int i = 0; i < 4; i++) {
		worldTransform_[i].Initialize();
	}

}

void Player::Update() {

	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.1f;

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A) {

			behaviorRequest_ = Behavior::kAttack;
		}

		move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;

		move.z += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;

		// move = Multiply(kCharacterSpeed, Normalize(move));

		Matrix4x4 rotateXMatrix = MakeRotateXMatrix(viewProjection_->rotation_.x);
		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);
		Matrix4x4 rotateZMatrix = MakeRotateZMatrix(viewProjection_->rotation_.z);

		Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

		move = TransformNormal(move, rotateXYZMatrix);

		if (move.x != 0 || move.z != 0) {

			for (int i = 0; i < 4; i++) {
				worldTransform_[0].rotation_.y = std::atan2(move.x, move.z);
			}
		}
	}

	

	for (int i = 0; i < 4; i++) {
		worldTransform_[0].translation_.x += move.x;
		worldTransform_[0].translation_.y += move.y;
		//worldTransform_[0].translation_.z += move.z;

		worldTransform_[i].UpdateMatrix();
	}

	

}

void Player::Draw(ViewProjection& viewProjection) {

	 for (int i = 0; i < 4; i++) {
		models_[i]->Draw(worldTransform_[i], viewProjection);
	}


}
