#pragma once
#include"ICommand.h"
class InputHandler
{
public:
	ICommand* HandleInput();
	void AssignMoveLCommand2PressKeyA();
	void AssignMoveRCommand2PressKeyD();
	void AssignMoveUCommand2PressKeyW();
	void AssignMoveDCommand2PressKeyS();
private:
	ICommand* pressKeyD_;
	ICommand* pressKeyA_;
	ICommand* pressKeyW_;
	ICommand* pressKeyS_;
};

