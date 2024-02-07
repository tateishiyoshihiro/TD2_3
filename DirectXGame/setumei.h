#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"

class setumei {

public:

	setumei();

	~setumei();
	
	void Initialize();
	
	void Update();

	void Draw();

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kGamePlay; }

private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Model* model_ = nullptr;

	bool isSceneEnd = false;

	uint32_t textureHandleS_ = 0;

	Sprite* spriteS_ = nullptr;

};
