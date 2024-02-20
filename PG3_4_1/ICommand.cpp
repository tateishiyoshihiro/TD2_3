#include "ICommand.h"
#include"Player.h"
ICommand::~ICommand()
{
}

void RCommand::Exec(Player& player)
{
	player.MoveR();
}

void LCommand::Exec(Player& player)
{
	player.MoveL();
}

void UCommand::Exec(Player& player)
{
	player.MoveU();
}

void DCommand::Exec(Player& player)
{
	player.MoveD();
}
