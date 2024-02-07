#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete sprite_;
}

void GameScene::Initialize() {
	worldTransform_.Initialize();

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//イラスト等
	textureHandleBack_ = TextureManager::Load("BackGround2.png");
	sprite_ = Sprite::Create(textureHandleBack_, {0, 0});

	   // 3Dモデル
	// ステージのモデルの初期化
	modelStage_T1_.reset(Model::CreateFromOBJ("T_stage_01", true));

	// チュートリアルステージ２

	// ステージ
	//modelStage_T2_.reset(Model::CreateFromOBJ("T_stage_02", true));

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

	enemy2_ = std::make_unique<Enemy2>();
	
	enemy2_->Initialize(enemyModels);

	enemy3_ = std::make_unique<Enemy3>();

	enemy3_->Initialize(enemyModels);

	enemyRed_ = std::make_unique<EnemyRed>();
	std::vector<Model*> enemyRedModels = {modelFighterEnemyRedBody_.get()};
	enemyRed_->Initialize(enemyRedModels);

	followCamera_->SetTarget(&player_->GetWorldTransform());

	player_->SetViewProjection(&followCamera_->GetViewProjection());

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	stage_T1_ = std::make_unique<Stage>();
	stage_T1_->Initialize(modelStage_T1_.get());

	//stage_T2_ = std::make_unique<Stage_2>();
	//stage_T2_->Initialize(modelStage_T2_.get());
}

void GameScene::Update() {

	enemy_->Update();
	enemy2_->Update();
	enemy3_->Update();


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



#endif // DEBUG
}


	
void GameScene::CheckAllCollisions() {

	Vector3 posA, posB;

	//自キャラと敵の当たり判定
	#pragma region

	posA = player_->GetWorldPosition();
	posB = enemy_->GetWorldPosition();
	
	float a1 = posA.x - posB.x;
	float b1 = posA.y - posB.y;
	float c1 = posA.z - posB.z;
	float d1 = sqrt(a1 * a1 + b1 * b1 + c1 * c1);

	if (d1 <= PlayerRadius + EnemyRadius) {

		player_->OnCollision();

		enemy_->OnCollision();
	}
	#pragma endregion

}		

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	sprite_->Draw();

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
	enemy2_->Draw(viewProjection_);
	enemy3_->Draw(viewProjection_);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);

	stage_T1_->Draw(viewProjection_);

	//stage_T2_->Draw(viewProjection_);

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

void GameScene::Reset() {

	//呼び出すときステージごとに中身を変える
	enemy_->Reset({0.0f, 0.0f, 5.0f});
	enemy2_->Reset({0.0f, 0.0f, 35.0f});
	enemy3_->Reset({0.0f, 0.0f, 30.0f});
	enemyRed_->Reset({0.0f, 0.0f, 5.0f});
}
