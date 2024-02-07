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

	void Reset(const Vector3& pos);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransformEnemyRed_Body_;
	//  モデル
	Model* model_ = nullptr;
	// 3Dモデル
	Model* modelFighterEnemyRedBody_;
	float enemyRedSpeed_ = -0.054f;
};
