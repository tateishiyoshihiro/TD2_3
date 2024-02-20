#pragma once
#include "Base.h"
class Monster : public Base
{
public:
	Monster();
	~Monster();
	void Born() override;
};