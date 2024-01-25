#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
}

void GameScene::Initialize() {
	worldTransform_.Initialize();

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	   // 3Dモデル

	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));

	viewProjection_.Initialize();

	followCamera_ = std::make_unique<FollowCamera>();
		//ステージの初期化
	stage_T1_->Initialize(modelStage_T1_.get());
	stage_T2_->Initialize(modelStage_T2_.get(), modelBridge_.get(), modelNeedleFloor_.get());
	
	followCamera_->Initialize();

	player_ = std::make_unique<Player>();

	std::vector<Model*> plyerModels = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get()};

	player_->Initialize(plyerModels);

	enemy_ = std::make_unique<Enemy>();
	std::vector<Model*> enemyModels = {modelFighterEnemyBody_.get()};
	enemy_->Initialize(enemyModels);

	enemyRed_ = std::make_unique<EnemyRed>();
	std::vector<Model*> enemyRedModels = {modelFighterEnemyRedBody_.get()};
	enemyRed_->Initialize(enemyRedModels);

	followCamera_->SetTarget(&player_->GetWorldTransform());

	player_->SetViewProjection(&followCamera_->GetViewProjection());


}

void GameScene::Update() {

	enemy_->Update();
	enemyRed_->Update();
	stage_T1_->Update();

	stage_T2_->Update();
	player_->Update();
	followCamera_->Update();
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
	viewProjection_.matView = followCamera_->GetViewProjection().matView;

	viewProjection_.TransferMatrix();

  #ifdef _DEBUG

	if (input_->PushKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}
	model_ = Model::Create();

	
	viewProjection_.UpdateMatrix();

	modelFighterEnemyBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	modelFighterEnemyRedBody_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	//
	std::vector<Model*> enemyModels = {modelFighterEnemyBody_.get()};
	std::vector<Model*> enemyRedModels = {modelFighterEnemyRedBody_.get()};

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	enemy_ = std::make_unique<Enemy>();
	enemyRed_ = std::make_unique<EnemyRed>();

	

	//チュートリアルステージ１

	//ステージのモデルの初期化
	modelStage_T1_.reset(Model::CreateFromOBJ("T_stage_01", true));

	//ステージの生成
	stage_T1_ = std::make_unique<Stage>();
	

	//チュートリアルステージ２

	//ステージ
	modelStage_T2_.reset(Model::CreateFromOBJ("T_stage_02", true));

	//トラップ、ギミックなど
	modelBridge_.reset(Model::CreateFromOBJ("ground", true));
	modelNeedleFloor_.reset(Model::CreateFromOBJ("ground", true));

	stage_T2_ = std::make_unique<Stage_2>();

	

	//ゲームステージ　１


	//ゲームステージ　２


	//エクストラステージ？？？（未定）

}

	


#endif // DEBUG
	
		
	



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

	player_->Draw(viewProjection_);


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

	// delete model_;

#pragma endregion
}
