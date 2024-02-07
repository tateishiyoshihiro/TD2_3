#include "GameClear.h"

void GameClear::Initialize() {}

void GameClear::Update() {

	XINPUT_STATE joyState;

	if (isSceneEnd == false) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {

			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {
				isSceneEnd = true;
			}
		}
	}
}

void GameClear::Draw() {}