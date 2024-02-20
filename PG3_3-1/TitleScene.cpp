#include "TitleScene.h"
#include "Novice.h"
void TitleScene::Init()
{
}

void TitleScene::Update()
{
 	if (keys_[DIK_SPACE] && !preKeys_[DIK_SPACE]) {
		sceneNo = kStage;
	}
}

void TitleScene::Draw()
{
	Novice::ScreenPrintf(1280 / 2, 720 / 2, "TitleScene");
}