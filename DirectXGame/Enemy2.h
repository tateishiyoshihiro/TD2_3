#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include"BaseCharacter.h"

class Enemy2 : public BaseCharacter {

   public:
	///< summary>
	// 初期化
	///  </summary>
	void Initialize(const std::vector<Model*>& models) override;

	/// <summary>
	// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection) override;

	Vector3 GetWorldPosition();

	void OnCollision();

	void Reset(const Vector3& pos);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformEnemy_Body_;
	//  モデル
	Model* model_ = nullptr;
	// 3Dモデル
	Model* modelFighterEnemyBody_;
	float enemySpeed_ = -0.054f;

};
