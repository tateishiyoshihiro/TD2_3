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
#include "Card.h"

class Player : public BaseCharacter {
	enum class Behavior {
		kRoot,
		kAttack,
		kJump,

	};

	

public:
	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjection) override;

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	 ~Player();

	// 通常行動更新
	void BehaviorRootUpdate();
	// 攻撃行動更新
	void BehaviorAttackUpdate();

	// 通常行動初期化
	void BehaviorRootInitialize();
	// 攻撃行動初期化
	void BehaviorAttackInitialize();

	// ジャンプ行動初期化
	void BehaviorJumpInitialize();
	// ジャンプ行動更新
	void BehaviorJumpUpdate();

	Vector3 GetWorldPosition();

	Vector3 GetWorldCardPosition();

	const WorldTransform& GetWorldTransform() { return worldTransform_[0]; }

	void Attack();

	//当たり判定
	void OnCollision();

	void HitJudgmentStage1();

	void Reset();

private:
	WorldTransform worldTransform_[4];

	Vector3 playerFromMin = {
	    worldTransform_[0].translation_.x - 1.0f,
	    worldTransform_[0].translation_.y,
	    worldTransform_[0].translation_.z - 1.0f,
	};
	Vector3 playerFromMax = {
	    worldTransform_[0].translation_.x + 1.0f,
	    worldTransform_[0].translation_.y + 3.0f,
	    worldTransform_[0].translation_.z + 1.0f,
	
	};

	ShortForm playerShortForm{
	    .minLeftBotom = {playerFromMin},
	    .minRightBotom = {playerFromMax.x,playerFromMin.y,playerFromMin.z},
	    .minLeftTop = {playerFromMin.x,playerFromMax.y,playerFromMin.z},
	    .minRightTop = {playerFromMax.x, playerFromMax.y, playerFromMin.z},

	    .maxLeftBotom = {playerFromMin.x, playerFromMin.y, playerFromMax.z},
	    .maxRightBotom = {playerFromMax.x, playerFromMin.y, playerFromMax.z},
	    .maxLeftTop = {playerFromMin.x, playerFromMax.y, playerFromMax.z},
	    .maxRightTop = {playerFromMax},

	};

	 	 
	 bool chek = false;



	Input* input_ = nullptr;

	 // 　カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

     // 振るまい
	Behavior behavior_ = Behavior::kRoot;

	std::optional<Behavior> behaviorRequest_ = std::nullopt;


	std::list <Card*> card_;

	bool sw = false;

	float X = 0;
	float Ease = 0;
   //速度
	Vector3 velocity_ = {};

	XINPUT_STATE joyStatePre;
	XINPUT_STATE joyState;

};
