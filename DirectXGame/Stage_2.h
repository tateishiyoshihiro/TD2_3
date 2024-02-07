#pragma once
#include "Model.h"
#include "WorldTransform.h"

#include "Input.h"

class Stage_2 {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	//当たり判定
	void OnCollision();

private:

	WorldTransform worldTransform_;

	Model* model_;

};
