#pragma once
#include "Transform.h"

class Enemy
{
public:

	void Initialize();

	void Update();

	void Draw();

	void Reset();

	void OnCollision();

	Transform GetTransform() { return transform_; }
	bool GetEnemyAlive() { return EnemyAlive; }

private:

	Transform transform_;

	int EnemySpeed = 3;

	bool EnemyAlive = true;
};

