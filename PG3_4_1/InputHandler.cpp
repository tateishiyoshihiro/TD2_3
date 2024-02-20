#include "InputHandler.h"
#include"Novice.h"
ICommand* InputHandler::HandleInput()
{
    if (Novice::CheckHitKey(DIK_D)) {
        return pressKeyD_;
    }
    if (Novice::CheckHitKey(DIK_A)){
        return pressKeyA_;
    }
    if (Novice::CheckHitKey(DIK_W)) {
        return pressKeyW_;
    }
    if (Novice::CheckHitKey(DIK_S)) {
        return pressKeyS_;
    }
    return nullptr;
}

void InputHandler::AssignMoveLCommand2PressKeyA()
{
    ICommand* command = new LCommand();
    pressKeyA_ = command;
}

void InputHandler::AssignMoveRCommand2PressKeyD()
{
    ICommand* command = new RCommand();
    pressKeyD_ = command;

}

void InputHandler::AssignMoveUCommand2PressKeyW()
{
    ICommand* command = new UCommand();
    pressKeyW_ = command;
}

void InputHandler::AssignMoveDCommand2PressKeyS()
{
    ICommand* command = new DCommand();
    pressKeyS_ = command;
}