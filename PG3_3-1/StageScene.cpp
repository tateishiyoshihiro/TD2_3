#include "StageScene.h"
#include"Novice.h"
StageScene::StageScene()
{
}

StageScene::~StageScene()
{
	delete player_;
	delete enemy_;
}

void StageScene::Init()
{
	player_ = new Player();
	player_->Initialize();

	enemy_ = new Enemy();
	enemy_->Initialize();

	BulletTransform = { 0,0,15 };
	input_ = Input::GetInstance();
}

void StageScene::Update()
{
	player_->Update();
	enemy_->Update();

	AllCollision();

	if (input_->TriggerKey(DIK_SPACE))
	{
		BulletAlive = true;
		BulletTransform = player_->GetTransform();
	}

	if (BulletAlive == true)
	{
		BulletTransform.y -= BulletSpeed;
	}

	if (BulletTransform.y <= 0)
	{
		BulletAlive = false;
	}

	if (enemy_->GetEnemyAlive() == false)
	{
		sceneNo = kClear;
		player_->Reset();
		enemy_->Reset();
		BulletAlive = false;
		BulletTransform = { 0,0,15 };
	}
}

void StageScene::Draw()
{
	player_->Draw();
	enemy_->Draw();

	if (BulletAlive == true)
	{
		Novice::DrawEllipse(BulletTransform.x, BulletTransform.y, BulletTransform.radius, BulletTransform.radius, 0.0f, BLUE, kFillModeSolid);
	}
	Novice::ScreenPrintf(1280 / 2, 720 / 2, "StageScene");
}

void StageScene::AllCollision()
{
	int a = BulletTransform.x - enemy_->GetTransform().x;
	int b = BulletTransform.y - enemy_->GetTransform().y;
	double d = sqrt(a * a + b * b);

	if (d <= BulletTransform.radius + enemy_->GetTransform().radius)
	{
		enemy_->OnCollision();
		BulletAlive = false;
	}
}