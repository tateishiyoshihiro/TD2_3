#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include"BaseCharacter.h"
class Enemy :public BaseCharacter {

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

private:
	enum ModelPartsIndex {
		kEnemyHeadIndex,
		kEnemyLIndex,
		kEnemyRIndex,
	};
	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformEnemy_Head_;
	WorldTransform worldTransformEnemy_L_;
	WorldTransform worldTransformEnemy_R_;
	
	// 3Dモデル
	Model* modelFighterEnemyHead_;
	Model* modelFighterEnemyL_;
	Model* modelFighterEnemyR_;
	float enemySpeed_ = 0.055f;
};
