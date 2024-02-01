#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	model_ = Model::Create();

	viewProjection_.Initialize();
	viewProjection_.UpdateMatrix();

	modelFighterEnemyHead_.reset(Model::CreateFromOBJ("BlackHead", true));
	modelFighterEnemyL_.reset(Model::CreateFromOBJ("BlackL", true));
	modelFighterEnemyR_.reset(Model::CreateFromOBJ("BlackR", true));
	modelFighterEnemyRedHead_.reset(Model::CreateFromOBJ("RedHead", true));
	modelFighterEnemyRedL_.reset(Model::CreateFromOBJ("RedL", true));
	modelFighterEnemyRedR_.reset(Model::CreateFromOBJ("RedR", true));
	//
	std::vector<Model*> enemyModels = {
	    modelFighterEnemyHead_.get(), modelFighterEnemyL_.get(),
		modelFighterEnemyR_.get()};
	std::vector<Model*> enemyRedModels = {
	    modelFighterEnemyRedHead_.get(), modelFighterEnemyRedL_.get(),
	    modelFighterEnemyRedR_.get()};

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(enemyModels);
	enemyRed_ = std::make_unique<EnemyRed>();
	enemyRed_->Initialize(enemyRedModels);
}

void GameScene::Update() {

	enemy_->Update();
	enemyRed_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	
	enemy_->Draw(viewProjection_);
	enemyRed_->Draw(viewProjection_);
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

	// delete model_;

#pragma endregion
}
