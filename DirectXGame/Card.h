#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Card {

	public:

		void Initialize( const Vector3& position, const Vector3& velocity);

	   void Update();

	   void Draw(const ViewProjection& viewProjection);

	   bool IsDead() const { return isDead_; }


	   void OnColision();

	   Vector3 GetWorldPosition();

	private:
	   WorldTransform worldTransform_;

	   Model* model_ = nullptr;

	   Vector3 velocity_={0, 0, 0};

	  uint32_t textureHandle_ = 0u;

	   static const int32_t kLifeTime = 20;

	   // デスタイマー
	   int32_t deathTimer_ = kLifeTime;

	   // デスフラグ
	   bool isDead_ = false;
};
