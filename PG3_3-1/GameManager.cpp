#include "GameManager.h"
#include"Novice.h"

GameManager::GameManager()
{
	sceneArr_[kTitle] = std::make_unique<TitleScene>();
	sceneArr_[kStage] = std::make_unique<StageScene>();
	sceneArr_[kClear] = std::make_unique<ClearScene>();

	for (int i = 0; i < kSceneMax; i++) {
		sceneArr_[i]->SetKeys(keys_, preKeys_);
	}
	currentSceneNo_ = kTitle;
}

GameManager::~GameManager()
{
}

int GameManager::Run()
{
	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();
		memcpy(preKeys_, keys_, 256);
		Novice::GetHitKeyStateAll(keys_);
		preSceneNo_ = currentSceneNo_;
		currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();
		if (preSceneNo_ != currentSceneNo_) {
			sceneArr_[currentSceneNo_]->Init();
		}
		sceneArr_[currentSceneNo_]->Update();
		sceneArr_[currentSceneNo_]->Draw();
		Novice::EndFrame();
		if (keys_[DIK_ESCAPE] == 0 && preKeys_[DIK_ESCAPE] != 0) {
			break;
		}
	}
	return 0;
}
