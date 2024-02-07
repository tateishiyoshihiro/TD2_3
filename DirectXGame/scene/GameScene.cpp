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
	// ステージのモデルの初期化
	modelStage_T1_.reset(Model::CreateFromOBJ("T_stage_01", true));

	// チュートリアルステージ２

	// ステージ
	modelStage_T2_.reset(Model::CreateFromOBJ("T_stage_02", true));

	// トラップ、ギミックなど
	modelBridge_.reset(Model::CreateFromOBJ("ground", true));
	modelNeedleFloor_.reset(Model::CreateFromOBJ("ground", true));

	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));

	modelFighterEnemyBody_.reset(Model::CreateFromOBJ("needle_Body", true));
	modelFighterEnemyRedBody_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	

	viewProjection_.Initialize();

	followCamera_ = std::make_unique<FollowCamera>();
		//ステージの初期化
	
	
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

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	stage_T1_ = std::make_unique<Stage>();
	stage_T1_->Initialize(modelStage_T1_.get());

	stage_T2_ = std::make_unique<Stage_2>();
	stage_T2_->Initialize(modelStage_T2_.get(), modelBridge_.get(), modelNeedleFloor_.get());
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

	XINPUT_STATE joyState;

	if (worldTransform_.translation_.z >= 100) {

		GoalFlag_ = true;
	}

	if (GoalFlag_ == true) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {

			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {

				GoalFlag_ = false;
				isSceneEnd = true;
			}
		}
	}

  #ifdef _DEBUG

	if (input_->PushKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}

	viewProjection_.UpdateMatrix();

}

#endif // DEBUG
	
void GameScene::CheckAllCollisions() {

	Vector3 posA, posB;

	//自キャラとステージ2の針の当たり判定
	#pragma region 

	posA = player_->GetWorldPosition();
	posB = stage_T2_->GetWorldPosition();

	float a = posA.x - posB.x;
	float b = posA.y - posB.y;
	float c = posA.z - posB.z;
	float d = sqrt(a * a + b * b + c * c);

	if (d <= PlayerRadius + NeedleFloorRadius) 
	{
		//自キャラの衝突時コールバックを呼び出す
		player_->OnCollision();
		//ステージ２の衝突時コールバックを呼び出す
		stage_T2_->OnCollision();
	}

	#pragma endregion

	//自キャラと敵の当たり判定
	#pragma region

	posA = player_->GetWorldPosition();
	posB = enemy_->GetWorldPosition();
	
	//float a1 = posA.x - posB.x;



	#pragma endregion

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


