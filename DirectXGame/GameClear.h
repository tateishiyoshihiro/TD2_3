#pragma once
#include "Scene.h"
#include "Input.h"

class GameClear {

public:
	void Initialize();

	void Update();

	void Draw();

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kTitle; }

private:
	bool isSceneEnd = false;


};
