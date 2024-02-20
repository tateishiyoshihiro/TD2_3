#include "Enemy.h"
#include "Novice.h"

void Enemy::Initialize()
{
	transform_ = { 640,200,20 };
}

void Enemy::Update()
{
	transform_.x += EnemySpeed;

	if (transform_.x + transform_.radius >= 1280)
	{
		EnemySpeed = EnemySpeed * -1;
	}

	if (transform_.x - transform_.radius < 0)
	{
		EnemySpeed = EnemySpeed * -1;
	}


}

void Enemy::Draw()
{
	if (EnemyAlive == true)
	{
		Novice::DrawEllipse(transform_.x, transform_.y, transform_.radius, transform_.radius, 0.0f, RED, kFillModeSolid);
	}
}

void Enemy::Reset()
{
	transform_ = { 640,200,20 };
	EnemyAlive = true;
}

void Enemy::OnCollision()
{
	EnemyAlive = false;
}
