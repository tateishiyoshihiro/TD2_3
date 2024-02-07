#include "EnemyRed.h"

 void EnemyRed::Initialize(const std::vector<Model*>& models) {
	//
	BaseCharacter::Initialize(models);
	worldTransform_.Initialize();
	worldTransformEnemyRed_Body_.scale_ = {2.0f, 2.0f, 2.0f};
	worldTransformEnemyRed_Body_.Initialize();
	worldTransformEnemyRed_Body_.translation_.y = 0.0f;
	worldTransformEnemyRed_Body_.translation_.x = 35.0f;
 }

void EnemyRed::Update() {
	// 速さ
	worldTransformEnemyRed_Body_.translation_.z += enemyRedSpeed_;
	worldTransformEnemyRed_Body_.translation_.z =
	    worldTransformEnemyRed_Body_.translation_.z + enemyRedSpeed_;
	if (worldTransformEnemyRed_Body_.translation_.z >= 10.0f) {
		enemyRedSpeed_ = -0.054f;
	}
	if (worldTransformEnemyRed_Body_.translation_.z <= -10.0f) {
		enemyRedSpeed_ = 0.054f;
	}
	//
	BaseCharacter::Update();
	// 行列を定数バッファに転送
	worldTransformEnemyRed_Body_.UpdateMatrix();
}

void EnemyRed::Draw(const ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransformEnemyRed_Body_, viewProjection);
}

Vector3 EnemyRed::GetWorldPosition() {
	Vector3 worldPos = {};

	worldPos.x = worldTransformEnemyRed_Body_.matWorld_.m[3][0];
	worldPos.y = worldTransformEnemyRed_Body_.matWorld_.m[3][1];
	worldPos.z = worldTransformEnemyRed_Body_.matWorld_.m[3][2];

	return worldPos;
}

void EnemyRed::OnCollision() {}


void EnemyRed::Reset(const Vector3& pos) { worldTransformEnemyRed_Body_.translation_ = pos; }