#include "Rectangle.h"
#include<stdio.h>
void Rectangle::size()
{
	radius = radius * radius;
}

void Rectangle::draw()
{
	printf("%f\n", radius);
}
