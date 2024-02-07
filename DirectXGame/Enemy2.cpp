#include "Enemy2.h"

void Enemy2::Initialize(const std::vector<Model*>& models) {//
	BaseCharacter::Initialize(models);
	worldTransform_.Initialize();
	worldTransformEnemy_Body_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformEnemy_Body_.Initialize();
	worldTransformEnemy_Body_.translation_.x = 15.0f;
}

void Enemy2::Update() {// 速さ
	// 速さ
	worldTransformEnemy_Body_.translation_.z += enemySpeed_;
	worldTransformEnemy_Body_.translation_.z =
	    worldTransformEnemy_Body_.translation_.z + enemySpeed_;
	if (worldTransformEnemy_Body_.translation_.z >= 10.0f) {
		enemySpeed_ = -0.055f;
	}
	if (worldTransformEnemy_Body_.translation_.z <= -0.0f) {
		enemySpeed_ = 0.055f;
	}
	//
	BaseCharacter::Update();
	// 行列を定数バッファに転送
	worldTransformEnemy_Body_.UpdateMatrix();

	
}

void Enemy2::Draw(const ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransformEnemy_Body_, viewProjection);
}

Vector3 Enemy2::GetWorldPosition() {
	Vector3 worldPos = {};

	worldPos.x = worldTransformEnemy_Body_.matWorld_.m[3][0];
	worldPos.y = worldTransformEnemy_Body_.matWorld_.m[3][1];
	worldPos.z = worldTransformEnemy_Body_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy2::OnCollision() {}

void Enemy2::Reset(const Vector3& pos) { 
	worldTransformEnemy_Body_.translation_ = pos;
}
