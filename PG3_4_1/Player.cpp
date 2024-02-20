#include "Player.h"
#include"Novice.h"
Player::Player()
{
	Init();
}

void Player::Init()
{
	pos_ = { 600.0f,300.0f };
	speed_ = 2.0f;
}

void Player::Update()
{
}

void Player::Draw()
{
	Novice::DrawEllipse((int)pos_.x, (int)pos_.y, 16, 16,0.0f, WHITE, kFillModeSolid);
}

void Player::MoveR()
{
	pos_.x += speed_;
}

void Player::MoveL()
{
	pos_.x -= speed_;
}
void Player::MoveU()
{
	pos_.y -= speed_;
}
void Player::MoveD()
{
	pos_.y += speed_;
}