#pragma once
#include "Scene.h"
#include "Input.h"

class TitleScene {

public:
	void Initialize();

	void Update();

	void Draw();

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kGamePlay; }

private:

	bool isSceneEnd = false;

};
