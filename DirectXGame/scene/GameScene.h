#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include <memory>
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "EnemyRed.h"
#include "Player.h"
#include "DebugCamera.h"
#include "FollowCamera.h"
#include "Scene.h"

#include "Stage.h"
#include "Stage_2.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kGameClear; }

    /// <summary>
    /// 衝突判定と応答
    /// </summary>
	void CheckAllCollisions();

	void Reset();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Model* model_ = nullptr;
	// 3Dモデル
	std::unique_ptr<Model> modelFighterEnemyBody_;// 体 
	std::unique_ptr<Model> modelFighterEnemyRedBody_;
	std::unique_ptr<Model> modelEnemy_;
	

	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	uint32_t textureHandle_ = 0;

	// 3Dモデル
	std::unique_ptr<Model> modelFighterBody_ = nullptr;
	std::unique_ptr<Model> modelFighterHead_ = nullptr;
	std::unique_ptr<Model> modelFighterL_arm_ = nullptr;
	std::unique_ptr<Model> modelFighterR_arm_ = nullptr;

	std::unique_ptr<Model> modelFighterEnemyHead_; // 体
	std::unique_ptr<Model> modelFighterEnemyL_;
	std::unique_ptr<Model> modelFighterEnemyR_;
	std::unique_ptr<Model> modelFighterEnemyRedHead_;
	std::unique_ptr<Model> modelFighterEnemyRedL_;
	std::unique_ptr<Model> modelFighterEnemyRedR_;

	std::unique_ptr<FollowCamera> followCamera_ = nullptr;

	std::unique_ptr<Player> player_ = nullptr;

	// 敵
	std::unique_ptr<Enemy> enemy_;
	std::unique_ptr<EnemyRed> enemyRed_;
	std::unique_ptr<Enemy2> enemy2_;
	std::unique_ptr<Enemy3> enemy3_;


	//worldTransformの初期化？
	WorldTransform worldTransform_;

	//チュートリアルステージ１

	//ステージクラスをゲームシーンに持たせる
	std::unique_ptr<Stage> stage_T1_;

	//ステージモデルを生成
	std::unique_ptr<Model> modelStage_T1_;

	//チュートリアルステージ２

	std::unique_ptr<Stage_2> stage_T2_;

	std::unique_ptr<Model> modelStage_T2_;

	// ゲームステージ　１

	// ゲームステージ　２

	// エクストラステージ？？？（未定）

	// viewProjectionの初期化？
	ViewProjection viewProjection_;

	bool GoalFlag_ = false;

	const int PlayerRadius = 15;
	const int EnemyRadius = 15;

	bool isSceneEnd = false;

	uint32_t textureHandleBack_ = 0;

	Sprite* sprite_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
