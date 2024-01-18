#pragma once
#include "Model.h"
#include "WorldTransform.h"

#include "Input.h"

class Stage_2 {
public:
	void Initialize(Model* model, Model* modelBridge, Model* modelNeedleFloor);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void NeedleFloorInitialize();

	void NeedleFloorUpdate();

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
