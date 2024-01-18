#pragma once
#include "Model.h"
#include "WorldTransform.h"

#include "Input.h"

class Stage_2 {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void NeedleFloorInitialize();

	void NeedleFloorUpdate();

private:

	WorldTransform worldTransform_;

	WorldTransform worldTransformBridge_;

	WorldTransform worldTransformNeedleFloor_;

	Model* model_ = nullptr;

	Model* modelBridge_;

	Model* modelNeedleFloor_;

	//フラグ

	bool GoalFlag_ = false;

	bool BridgeFlag_ = false;

	bool NeedleFloorFlag_ = false;

	//変数？

	int NeedleFlame_ = 240;

};
