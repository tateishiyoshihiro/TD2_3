#include "setumei.h"

setumei::setumei() {}

setumei::~setumei() {

	delete spriteS_;

}

void setumei::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandleS_ = TextureManager::Load("setumei.png");
	spriteS_ = Sprite::Create(textureHandleS_, {0, 0});

}

void setumei::Update() {

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
	} else {
		isSceneEnd = false;
	}

}

void setumei::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	spriteS_->Draw();

	Sprite::PostDraw();


}
