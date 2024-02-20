#include<stdio.h>
#include"IShape.h"
#include"Circle.h"
#include"Rectangle.h"
int main() {
	IShape* iShape_[2]{};
	for (int i = 0; i < 2; i++) {
		if (i < 1) {
			iShape_[i] = new Circle();
		}
		else {
			iShape_[i] = new Rectangle();
		}
	}
	for (int i = 0; i < 2; i++) {
		iShape_[i]->size();
	}
	for (int i = 0; i < 2; i++) {
		iShape_[i]->draw();
	}
	for (int i = 0; i < 2; i++) {
		delete iShape_[i];
	}
	return 0;
}