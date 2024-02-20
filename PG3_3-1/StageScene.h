#pragma once
#include"IScene.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"
#include "Transform.h"
class StageScene:public IScene
{
public:
	StageScene();
	~StageScene();
	void Init()override;
	void Update()override;
	void Draw()override;
	void AllCollision();
private:
	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;
	Input* input_ = nullptr;
	Transform BulletTransform;
	int BulletSpeed = 4;
	bool BulletAlive = true;
};

