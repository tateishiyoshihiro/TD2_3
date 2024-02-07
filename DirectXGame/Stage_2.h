#pragma once
#include "Model.h"
#include "WorldTransform.h"

#include "Input.h"

class Stage_2 {
public:
	void Initialize(Model* model, Model* modelBridge, Model* modelNeedleFloor);

	void Update();

	void Draw(ViewProjection& viewProjection);

	//針ギミック初期化
	void NeedleFloorInitialize();

	//針ギミック更新
	void NeedleFloorUpdate();

	//当たり判定
	void OnCollision();

	Vector3 GetWorldPosition();

	const WorldTransform& GetWorldTransformNeedleFloor() { return worldTransformNeedleFloor_; }

	//const WorldTransform& SetWorldTransformNeedleFloor() { worldTransformNeedleFloor_; }

private:

	WorldTransform worldTransform_;

	WorldTransform worldTransformBridge_;

	WorldTransform worldTransformNeedleFloor_;

	Model* model_;

	Model* modelBridge_;

	Model* modelNeedleFloor_;

	//フラグ

	//ゴール
	bool GoalFlag_ = false;

	//橋
	bool BridgeFlag_ = false;

	//トラップ（床針）
	bool NeedleFloorFlag_ = false;

	//変数？

	int NeedleFlame_ = 240;

};
