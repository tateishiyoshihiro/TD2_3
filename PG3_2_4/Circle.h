#pragma once
#include"IShape.h"
class Circle:public IShape
{
public:
	void size();
	void draw();
private:
	float radius = 30.0f;
	float pi = 3.14f;
};

