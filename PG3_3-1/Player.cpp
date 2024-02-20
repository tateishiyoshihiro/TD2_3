#include "Player.h"
#include "Novice.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	transform_ = { 640, 400,20 };
	input_ = Input::GetInstance();
}

void Player::Update()
{

	const int kPlayerSpeed = 5;

	if (input_->PushKey(DIK_D))
	{
		transform_.x += kPlayerSpeed;
	}
	if (input_->PushKey(DIK_A))
	{
		transform_.x -= kPlayerSpeed;
	}

	if (input_->PushKey(DIK_W))
	{
		transform_.y -= kPlayerSpeed;
	}
	if (input_->PushKey(DIK_S))
	{
		transform_.y += kPlayerSpeed;
	}

}

void Player::Draw()
{
	Novice::DrawEllipse(transform_.x, transform_.y, transform_.radius, transform_.radius, 0.0f, WHITE, kFillModeSolid);
}

void Player::Reset()
{
	transform_ = { 640,400,20 };
}
