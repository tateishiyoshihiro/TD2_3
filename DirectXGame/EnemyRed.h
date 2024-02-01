#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include"BaseCharacter.h"
class EnemyRed : public BaseCharacter {

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
		kEnemyRedHeadIndex,
		kEnemyRedLIndex,
		kEnemyRedRIndex,
	};
	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformEnemyRed_Head_;
	WorldTransform worldTransformEnemyRed_L_;
	WorldTransform worldTransformEnemyRed_R_;
	
	// 3Dモデル
	Model* modelFighterEnemyRedHead_;
	Model* modelFighterEnemyRedL_;
	Model* modelFighterEnemyRedR_;
	float enemyRedSpeed_ = -0.054f;
};
