#pragma once
#include "Input.h"
#include "Transform.h"
class Player
{
public:

	Player();

	~Player();

	void Initialize();

	void Update();

	void Draw();

	void Reset();

	Transform GetTransform() { return transform_; }

private:

	Transform transform_;

	Input* input_ = nullptr;
};

