#include "Circle.h"
#include<stdio.h>
void Circle::size()
{
	radius = radius * radius * pi;
}

void Circle::draw()
{
	printf("%f\n", radius);
}
