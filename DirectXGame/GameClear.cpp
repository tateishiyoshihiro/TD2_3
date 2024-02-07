#include "GameClear.h"

void GameClear::Initialize() {}

void GameClear::Update() {

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

void GameClear::Draw() {}