#include "BaseCharacter.h"

void BaseCharacter::Initalize(const std::vector<Model*>& models) {

void BaseCharacter::Initialize(const std::vector<Model*>& models) { 
	models_ = models;

	worldTransform_.Initialize();

}

void BaseCharacter::Update() {

	// 行列を更新
	worldTransform_.UpdateMatrix();

}

void BaseCharacter::Draw(ViewProjection& viewProjection) {

void BaseCharacter::Draw(const ViewProjection& viewProjection) {
	//
for (Model* model : models_) {
	

model->Draw(worldTransform_, viewProjection);

}



}
