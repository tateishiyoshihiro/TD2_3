#include "TitleScene.h"
#include "TextureManager.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {

	delete sprite_;

}

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("Title.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});
}

void TitleScene::Update() {

	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;

	if (isSceneEnd == false) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			Input::GetInstance()->GetJoystickStatePrevious(0, joyStatePre);
			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B &&
			    joyStatePre.Gamepad.wButtons != XINPUT_GAMEPAD_B) {
				isSceneEnd = true;
			}
		}
	} 
	else 
	{
		isSceneEnd = false;
	}
}

void TitleScene::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	sprite_->Draw();

	Sprite::PostDraw();

}
