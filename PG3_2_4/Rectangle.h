#pragma once
#include"IShape.h"
class Rectangle:public IShape
{
public:
	void size();
	void draw();
private:
	float radius = 30.0f;
};

