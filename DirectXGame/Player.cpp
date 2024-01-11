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

if (behaviorRequest_) {

		behavior_ = behaviorRequest_.value();

		switch (behavior_) {
		case Behavior::kRoot:
		default:
			BehaviorRootInitialize();
			break;
		case Behavior::kAttack:

			BehaviorAttackInitialize();

			break;

		case Behavior::kJump:

		BehaviorJumpInitialize();

		break;

		}
		// 振る舞いリセット
		behaviorRequest_ = std::nullopt;
	}

	switch (behavior_) {
	case Behavior::kRoot:
	default:
		BehaviorRootUpdate();

		break;
	case Behavior::kAttack:

		BehaviorAttackUpdate();

		break;

	case Behavior::kJump:

		BehaviorJumpUpdate();

		break;


	}

	

	for (int i = 0; i < 4; i++) {

		worldTransform_[i].UpdateMatrix();
	}
	

}

void Player::Draw(ViewProjection& viewProjection) {

	 for (int i = 0; i < 4; i++) {
		models_[i]->Draw(worldTransform_[i], viewProjection);
	}


}



void Player::BehaviorRootUpdate() {

	BaseCharacter::Update();

	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;

	


	XINPUT_STATE joyState;

	

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		velocity_ = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed};

		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {

			behaviorRequest_ = Behavior::kAttack;
		}
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A ) {

			behaviorRequest_ = Behavior::kJump;
		}

		

		// move = Multiply(kCharacterSpeed, Normalize(move));

		Matrix4x4 rotateXMatrix = MakeRotateXMatrix(viewProjection_->rotation_.x);
		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);
		Matrix4x4 rotateZMatrix = MakeRotateZMatrix(viewProjection_->rotation_.z);

		Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

		velocity_ = TransformNormal(velocity_, rotateXYZMatrix);

		if (velocity_.x != 0 || velocity_.z != 0) {

			for (int i = 0; i < 4; i++) {
				worldTransform_[0].rotation_.y = std::atan2(velocity_.x, velocity_.z);
			}
		}
	}

	

	for (int i = 0; i < 4; i++) {
		worldTransform_[0].translation_.x += velocity_.x;
		worldTransform_[0].translation_.y += velocity_.y;
		//worldTransform_[0].translation_.z += velocity_.z;

		worldTransform_[i].UpdateMatrix();
	}
}

void Player::BehaviorAttackUpdate() {

	X += 0.05f;

	

	

	if (X >= 2.6) {

		X = 0;

		behaviorRequest_ = Behavior::kRoot;
	}
}

void Player::BehaviorRootInitialize() {

	worldTransform_[2].scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_[2].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[2].translation_ = {-0.51f, 1.26f, 0.0f};

	worldTransform_[3].scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_[3].rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[3].translation_ = {0.51f, 1.26f, 0.0f};
}

void Player::BehaviorAttackInitialize() {

	worldTransform_[0].translation_.y = 0.0f;

	worldTransform_[2].scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_[2].rotation_ = {3.0f, 0.0f, 0.0f};
	worldTransform_[2].translation_ = {-0.51f, 1.26f, 0.0f};

	worldTransform_[3].scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_[3].rotation_ = {3.0f, 0.0f, 0.0f};
	worldTransform_[3].translation_ = {0.51f, 1.26f, 0.0f};

	
	X = 0;
}

void Player::BehaviorJumpInitialize() {
	worldTransform_[0].translation_.y = 0.0f;

	
	worldTransform_[2].rotation_.x = 0;
	;
	worldTransform_[3].rotation_.x = 0;
	
	const float kJumpFirstSpeed = 1.0f;



	velocity_.y =  kJumpFirstSpeed;


}

void Player::BehaviorJumpUpdate() {

	worldTransform_[0].translation_.x += velocity_.x;

	worldTransform_[0].translation_.y += velocity_.y;

	const float kGravityAcceleration = 0.06f;

	Vector3 accelerationVector = {0, -kGravityAcceleration, 0};

	velocity_ = Add(velocity_,accelerationVector);

	if (worldTransform_[0].translation_.y < 0.0f) {
		worldTransform_[0].translation_.y = 0;
	
		  behaviorRequest_ = Behavior::kRoot;
	
	}




}
