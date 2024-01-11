#include "EnemyRed.h"
#include "MathUtilityForText.h"

 void EnemyRed::Initialize(const std::vector<Model*>& models) {
	//
	BaseCharacter::Initialize(models);
	worldTransformEnemyRed_Body_.Initialize();

	
	worldTransformEnemyRed_Body_.translation_.z = -35.0f;
 }

void EnemyRed::Update() {
	// 速さ
	worldTransformEnemyRed_Body_.translation_.x += enemyRedSpeed_;
	worldTransformEnemyRed_Body_.translation_.x =
	    worldTransformEnemyRed_Body_.translation_.x + enemyRedSpeed_;
	if (worldTransformEnemyRed_Body_.translation_.x >= 5.0f) {
		enemyRedSpeed_ = -0.054f;
	}
	if (worldTransformEnemyRed_Body_.translation_.x <= -5.0f) {
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