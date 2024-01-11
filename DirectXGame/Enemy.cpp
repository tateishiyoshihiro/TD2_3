﻿#include "Enemy.h"
#include "MathUtilityForText.h"

 void Enemy::Initialize(const std::vector<Model*>& models) {
	//
	 BaseCharacter::Initialize(models);
	 worldTransformEnemy_Body_.Initialize();
 }

void Enemy::Update() {
	 // 速さ
	 worldTransformEnemy_Body_.translation_.x += enemySpeed_;
	 worldTransformEnemy_Body_.translation_.x = worldTransformEnemy_Body_.translation_.x + enemySpeed_;
	 if (worldTransformEnemy_Body_.translation_.x >= 10.0f) {
		 enemySpeed_ = -0.055f;
	 }
	 if (worldTransformEnemy_Body_.translation_.x <= -0.0f) {
		 enemySpeed_ = 0.055f;
	 }
	 //
	 BaseCharacter::Update();
	// 行列を定数バッファに転送
	worldTransformEnemy_Body_.UpdateMatrix();

	worldTransformEnemy_Body_.translation_.z = -35.0f;
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransformEnemy_Body_, viewProjection);
}
