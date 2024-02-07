#include "Enemy.h"
#include "Func.h"

 void Enemy::Initialize(const std::vector<Model*>& models) {
	//
	 BaseCharacter::Initialize(models);
	 worldTransform_.Initialize();
	 worldTransformEnemy_Body_.scale_ = {2.0f, 2.0f, 2.0f};
	 worldTransformEnemy_Body_.Initialize();
	 worldTransformEnemy_Body_.translation_.x = 70.0f;
	 worldTransformEnemy_Body_.translation_.y = 0.0f;
 }

void Enemy::Update() {
	 // 速さ
	 worldTransformEnemy_Body_.translation_.z += enemySpeed_;
	 worldTransformEnemy_Body_.translation_.z = worldTransformEnemy_Body_.translation_.z + enemySpeed_;
	 if (worldTransformEnemy_Body_.translation_.z >= 10.0f) {
		 enemySpeed_ = -0.055f;
	 }
	 if (worldTransformEnemy_Body_.translation_.z <= -10.0f) {
		 enemySpeed_ = 0.055f;
	 }
	 //
	 BaseCharacter::Update();
	// 行列を定数バッファに転送
	worldTransformEnemy_Body_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransformEnemy_Body_, viewProjection);
}

Vector3 Enemy::GetWorldPosition() {

	Vector3 worldPos = {};

	worldPos.x = worldTransformEnemy_Body_.matWorld_.m[3][0];
	worldPos.y = worldTransformEnemy_Body_.matWorld_.m[3][1];
	worldPos.z = worldTransformEnemy_Body_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::Reset(const Vector3& pos) {


worldTransformEnemy_Body_.translation_ = pos;


}

void Enemy::OnCollision() {}
