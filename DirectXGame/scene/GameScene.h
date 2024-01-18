#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Enemy.h"
#include"EnemyRed.h"
#include <memory>
  #include "Player.h"
#include <memory>
#include "DebugCamera.h"
#include "FollowCamera.h"

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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	ViewProjection viewProjection_;
	// 3Dモデル
	std::unique_ptr<Model> modelFighterEnemyBody_;// 体 
	std::unique_ptr<Model> modelFighterEnemyRedBody_;
	std::unique_ptr<Model> modelEnemy_;
	

	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	uint32_t textureHandle_ = 0;
	std::unique_ptr<Model> model_ = nullptr;

	// 3Dモデル
	std::unique_ptr<Model> modelFighterBody_ = nullptr;
	std::unique_ptr<Model> modelFighterHead_ = nullptr;
	std::unique_ptr<Model> modelFighterL_arm_ = nullptr;
	std::unique_ptr<Model> modelFighterR_arm_ = nullptr;

	std::unique_ptr<FollowCamera> followCamera_ = nullptr;

	ViewProjection viewProjection_;
	std::unique_ptr<Player> player_ = nullptr;

	// 敵
	std::unique_ptr<Enemy> enemy_;
	std::unique_ptr<EnemyRed> enemyRed_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
