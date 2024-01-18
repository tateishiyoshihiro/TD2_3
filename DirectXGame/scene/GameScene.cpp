#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	viewProjection_.Initialize();

	//チュートリアルステージ１

	//ステージのモデルの初期化
	modelStage_T1_.reset(Model::CreateFromOBJ("ground", true));

	//ステージの生成
	stage_T1_ = std::make_unique<Stage>();
	//ステージの初期化
	stage_T1_->Initialize(modelStage_T1_.get());

	//チュートリアルステージ２

	modelStage_T2_.reset(Model::CreateFromOBJ("ground", true));

	stage_T2_ = std::make_unique<Stage_2>();

	stage_T2_->Initialize(modelStage_T2_.get());

	//ゲームステージ　１


	//ゲームステージ　２


	//エクストラステージ？？？（未定）

}

void GameScene::Update() {

	stage_T1_->Update();

	stage_T2_->Update();
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

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	stage_T1_->Draw(viewProjection_);

	stage_T2_->Draw(viewProjection_);

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

#pragma endregion
}
