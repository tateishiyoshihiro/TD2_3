#include "Player.h"
#include "assert.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "ImGuiManager.h"

void Player::Initialize(const std::vector<Model*>& models) {

	   BaseCharacter::Initialize(models);

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

	  // デスフラグの立った弾を削除
	card_.remove_if([](Card* card) {
		if (card->IsDead()) {
			delete card;

			return true;
		}
		return false;
	});
		
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
	
		

	for (Card* card : card_) {
		card->Update();
	}

}

void Player::Draw(const ViewProjection& viewProjection) {

	 for (int i = 0; i < 4; i++) {
		models_[i]->Draw(worldTransform_[i], viewProjection);
	}

	 for (Card* card : card_) {
		card->Draw(viewProjection);
	}

}

Player::~Player() {
	for (Card* card : card_) {

		delete card;
	}

}

void Player::BehaviorRootUpdate() {

	BaseCharacter::Update();

	Attack();

	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;

	//XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		velocity_ = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX , 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX };

		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {

			behaviorRequest_ = Behavior::kAttack;
		}
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A ) {

			behaviorRequest_ = Behavior::kJump;
		}

		

		 velocity_ = Multiply(kCharacterSpeed, Normalize(velocity_));
		// move = Multiply(kCharacterSpeed, Normalize(move));

		Matrix4x4 rotateXMatrix = MakeRotateXMatrix(viewProjection_->rotation_.x);
		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);
		Matrix4x4 rotateZMatrix = MakeRotateZMatrix(viewProjection_->rotation_.z);

		Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

		velocity_ = TransformNormal(velocity_, rotateXYZMatrix);

		/*if (velocity_.x != 0 && velocity_.x >= 0.01) {
				worldTransform_[0].rotation_.y = 1.57f;
		} else if (velocity_.x != 0 && velocity_.x <= -0.01)
			    worldTransform_[0].rotation_.y =- 1.57f;
		}*/

		if (velocity_.x != 0 || velocity_.z != 0) {
			worldTransform_[0].rotation_.y = std::atan2(velocity_.x, velocity_.z);
		}


	}

	for (int i = 0; i < 4; i++) {
		worldTransform_[0].translation_.x += velocity_.x;
		worldTransform_[0].translation_.y += velocity_.y;
		worldTransform_[0].translation_.z += velocity_.z;

		worldTransform_[i].UpdateMatrix();
	}

	#ifdef _DEBUG
	ImGui::Begin("Player");

	 ImGui::DragFloat3("Rota", &velocity_.x, 0.01f);
	ImGui::DragFloat3("Rotation", &worldTransform_[0].rotation_.x, 0.01f);
	 ImGui::DragFloat3("Rotation", &worldTransform_[0].translation_.x, 0.01f);

	ImGui::End();

#endif

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

	worldTransform_[0].translation_.z += velocity_.z;

	const float kGravityAcceleration = 0.06f;

	Vector3 accelerationVector = {0, -kGravityAcceleration, 0};

	velocity_ = Add(velocity_,accelerationVector);

	if (worldTransform_[0].translation_.y < 0.0f) {
		worldTransform_[0].translation_.y = 0;
	
		  behaviorRequest_ = Behavior::kRoot;
	}
}

Vector3 Player::GetWorldPosition() { 

	   Vector3 worldPos = {};

	worldPos.x = worldTransform_[0].matWorld_.m[3][0];
	worldPos.y = worldTransform_[0].matWorld_.m[3][1];
	worldPos.z = worldTransform_[0].matWorld_.m[3][2];

	return worldPos;


}

Vector3 Player::GetWorldCardPosition() {
	Vector3 worldPos = {};

	worldPos.x = worldTransform_[0].matWorld_.m[3][0];
	worldPos.y = worldTransform_[0].matWorld_.m[3][1] + 5;
	worldPos.z = worldTransform_[0].matWorld_.m[3][2];

	return worldPos;
}

void Player::Attack() {


	

	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {

		  return;
	}
	Input::GetInstance()->GetJoystickStatePrevious(0, joyStatePre);
	

	if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_SHOULDER &&
	    joyStatePre.Gamepad.wButtons != XINPUT_GAMEPAD_RIGHT_SHOULDER) {

		  const float kCardSpeed = 1.0f;
		  Vector3 velocity(0, 0, kCardSpeed);

		  Vector3 playerWorld = GetWorldCardPosition();

		  if (velocity_.z<= -1) {

			velocity.z = -kCardSpeed;
		  } else {
		  
		  	  velocity.z = kCardSpeed;
		  }

		  velocity = Multiply(kCardSpeed, Normalize(velocity));

		  velocity = TransformNormal(velocity, worldTransform_[0].matWorld_);

		 Card* newCard_ = new Card();

		 newCard_->Initialize(playerWorld, velocity);
		
		 card_.push_back(newCard_);
		 
		 sw = true;
	}
}
