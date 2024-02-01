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
	std::unique_ptr<Model> modelFighterEnemyHead_; // 体
	std::unique_ptr<Model> modelFighterEnemyL_;
	std::unique_ptr<Model> modelFighterEnemyR_;
	std::unique_ptr<Model> modelFighterEnemyRedHead_;
	std::unique_ptr<Model> modelFighterEnemyRedL_;
	std::unique_ptr<Model> modelFighterEnemyRedR_;
	std::unique_ptr<Model> modelEnemy_;
	

	// 敵
	std::unique_ptr<Enemy> enemy_;
	std::unique_ptr<EnemyRed> enemyRed_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
