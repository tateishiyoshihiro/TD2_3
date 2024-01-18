#include "Card.h"
#include "cassert"

void Card::Initialize( const Vector3& position, const Vector3& velocity) 
{
	

	model_ = Model::Create();
	
	textureHandle_ = TextureManager::Load("debugfont.png");

	
	worldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransform_.translation_ = position;

	worldTransform_.Initialize();

	velocity_ = velocity;

}

void Card::Update() {

	worldTransform_.UpdateMatrix();

	worldTransform_.translation_.y += velocity_.y;

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}


}


void Card::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}

void Card::OnColision() {

   isDead_ = true;

}

Vector3 Card::GetWorldPosition() { 

   Vector3 worldPos = {};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;


}
