#pragma once

#include "Model.h"
#include "WorldTransform.h"

#include "Input.h"

#include "Stage_2.h"

class Stage {
public:

	void Initialize(Model* model); 

	void Update();

	void Draw(ViewProjection& viewProjection);

private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	bool GoalFlag_ = false;
};
