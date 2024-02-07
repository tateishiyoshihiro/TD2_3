#include "TitleScene.h"

void TitleScene::Initialize() {}

void TitleScene::Update() {

	XINPUT_STATE joyState;

	if (isSceneEnd == false) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {

			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {
				isSceneEnd = true;
			}
		}
	}
}

void TitleScene::Draw() {}
