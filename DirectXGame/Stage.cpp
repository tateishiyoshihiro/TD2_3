#include "Stage.h"
#include <cassert>

void Stage::Initialize(Model* model) {

	assert(model);

	model_ = model;

	worldTransform_.Initialize();
}

void Stage::Update() { 
	



	worldTransform_.TransferMatrix(); 
}

void Stage::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}
