#include "Enemy.h"
#include "MathUtilityForText.h"

 void Enemy::Initialize(const std::vector<Model*>& models) {
	 BaseCharacter::Initialize(models);
	 worldTransform_.Initialize();
	 worldTransformEnemy_Head_.parent_ = &worldTransform_;
	 worldTransformEnemy_L_.parent_ = &worldTransformEnemy_Head_;
	 worldTransformEnemy_R_.parent_ = &worldTransformEnemy_Head_;

	 worldTransformEnemy_Head_.Initialize();
	 worldTransformEnemy_L_.Initialize();
	 worldTransformEnemy_R_.Initialize();
 }

void Enemy::Update() {
	 // 速さ
	/* worldTransformEnemy_Head_.translation_.x += enemySpeed_;
	 worldTransformEnemy_Head_.translation_.x = worldTransformEnemy_Head_.translation_.x + enemySpeed_;
	 if (worldTransformEnemy_Head_.translation_.x >= 10.0f) {
		 enemySpeed_ = -0.055f;
	 }
	 if (worldTransformEnemy_Head_.translation_.x <= -0.0f) {
		 enemySpeed_ = 0.055f;
	 }*/
	worldTransformEnemy_Head_.translation_.z = 2.0f;
	 //
	 BaseCharacter::Update();
	// 行列を定数バッファに転送
	worldTransformEnemy_Head_.UpdateMatrix();
	worldTransformEnemy_L_.UpdateMatrix();
	worldTransformEnemy_R_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	models_[kEnemyHeadIndex]->Draw(worldTransformEnemy_Head_, viewProjection);
	models_[kEnemyLIndex]->Draw(worldTransformEnemy_L_, viewProjection);
	models_[kEnemyRIndex]->Draw(worldTransformEnemy_R_, viewProjection);
}
