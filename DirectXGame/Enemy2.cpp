#include "Enemy2.h"

void Enemy2::Initialize(const std::vector<Model*>& models) {//
	BaseCharacter::Initialize(models);
	worldTransform_.Initialize();
	worldTransformEnemy_Body_.Initialize();
}

void Enemy2::Update() {// ����
	// ����
	worldTransformEnemy_Body_.translation_.x += enemySpeed_;
	worldTransformEnemy_Body_.translation_.x =
	    worldTransformEnemy_Body_.translation_.x + enemySpeed_;
	if (worldTransformEnemy_Body_.translation_.x >= 10.0f) {
		enemySpeed_ = -0.055f;
	}
	if (worldTransformEnemy_Body_.translation_.x <= -0.0f) {
		enemySpeed_ = 0.055f;
	}
	//
	BaseCharacter::Update();
	// �s���萔�o�b�t�@�ɓ]��
	worldTransformEnemy_Body_.UpdateMatrix();

	worldTransformEnemy_Body_.translation_.z = -35.0f;
}

void Enemy2::Draw(const ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransformEnemy_Body_, viewProjection);
}

void Enemy2::Reset(const Vector3& pos) { 
	worldTransformEnemy_Body_.translation_ = pos;
}