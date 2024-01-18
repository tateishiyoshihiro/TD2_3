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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

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

	std::unique_ptr<Model> modelNeedleFloor_;

	std::unique_ptr<Model> modelBridge_;

	// ゲームステージ　１

	// ゲームステージ　２

	// エクストラステージ？？？（未定）

	// viewProjectionの初期化？
	ViewProjection viewProjection_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
