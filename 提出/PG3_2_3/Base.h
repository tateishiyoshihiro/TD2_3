#pragma once
#include<stdio.h>
class Base
{
public:
	Base();
	virtual ~Base();
	virtual void Born();
protected:
	const char* name_;
};

