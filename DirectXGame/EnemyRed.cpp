#include "EnemyRed.h"
#include "MathUtilityForText.h"

 void EnemyRed::Initialize(const std::vector<Model*>& models) {
	BaseCharacter::Initialize(models);
	 worldTransformEnemyRed_Head_.parent_ = &worldTransform_;
	 worldTransformEnemyRed_L_.parent_ = &worldTransformEnemyRed_Head_;
	 worldTransformEnemyRed_R_.parent_ = &worldTransformEnemyRed_Head_;


	worldTransformEnemyRed_Head_.Initialize();
	worldTransformEnemyRed_L_.Initialize();
	worldTransformEnemyRed_R_.Initialize();
	
	worldTransformEnemyRed_Head_.translation_.z = 0.0f;
 }

void EnemyRed::Update() {
	// 速さ
	/*worldTransformEnemyRed_Head_.translation_.x += enemyRedSpeed_;
	worldTransformEnemyRed_Head_.translation_.x =
	    worldTransformEnemyRed_Head_.translation_.x + enemyRedSpeed_;
	if (worldTransformEnemyRed_Head_.translation_.x >= 5.0f) {
		enemyRedSpeed_ = -0.054f;
	}
	if (worldTransformEnemyRed_Head_.translation_.x <= -5.0f) {
		enemyRedSpeed_ = 0.054f;
	}*/
	//
	BaseCharacter::Update();
	// 行列を定数バッファに転送
	worldTransformEnemyRed_Head_.UpdateMatrix();
	worldTransformEnemyRed_L_.UpdateMatrix();
	worldTransformEnemyRed_R_.UpdateMatrix();
}

void EnemyRed::Draw(const ViewProjection& viewProjection) {
	models_[kEnemyRedHeadIndex]->Draw(worldTransformEnemyRed_Head_, viewProjection);
	models_[kEnemyRedLIndex]->Draw(worldTransformEnemyRed_L_, viewProjection);
	models_[kEnemyRedRIndex]->Draw(worldTransformEnemyRed_R_, viewProjection);
}