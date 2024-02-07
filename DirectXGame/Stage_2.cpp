#include "Stage_2.h"
#include <cassert>

#include "ImGuiManager.h"

void Stage_2::Initialize(Model* model) {
	
	assert(model);

	model_ = model;
	
	worldTransform_.Initialize();
}

void Stage_2::Update() {

}

void Stage_2::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}

void Stage_2::OnCollision() {


}

