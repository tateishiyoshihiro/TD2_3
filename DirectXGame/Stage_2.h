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

	Model* model_ = nullptr;

	Model* modelBridge_;

	bool GoalFlag_ = false;

	bool BridgeFlag_ = false;

	bool NeedleFloorFlag_ = false;

	int NeedleFlame_ = 240;

	float NeedleSpeed_ = 0.5f;

};
