#pragma once
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "Windows.h"
#include "WorldTransform.h"
#include <list>
#include <optional>
#include "Func.h"

#include "BaseCharacter.h"

class Player : public BaseCharacter {
	enum class Behavior {
		kRoot,
		kAttack,
		kJump,

	};

public:
	void Initalize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(ViewProjection& viewProjection) override;

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	//Vector3 GetWorldPosition();

	// 通常行動更新
	void BehaviorRootUpdate();
	// 攻撃行動更新
	void BehaviorAttackUpdate();

	// 通常行動初期化
	void BehaviorRootInitialize();
	// 攻撃行動初期化
	void BehaviorAttackInitialize();


private:
	WorldTransform worldTransform_[4];

	


	Input* input_ = nullptr;

	 // 　カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

     // 振るまい
	Behavior behavior_ = Behavior::kRoot;

	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	float X = 0;
	float Ease = 0;
};
