#pragma once
class Player;
class ICommand
{
public:
	virtual ~ICommand();
	virtual void Exec(Player& player) = 0;
};
class RCommand:public ICommand
{
public:
	void Exec(Player& player)override;
};
class LCommand :public ICommand
{
public:
	void Exec(Player& player)override;
};
class UCommand :public ICommand
{
public:
	void Exec(Player& player)override;
};
class DCommand :public ICommand
{
public:
	void Exec(Player& player)override;
};



