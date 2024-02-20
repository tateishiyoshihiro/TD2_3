#include <stdio.h>
#include "Monster.h"
#include "Monster2.h"
int main() {
	printf("\n");
	Base* Cars[2];
	Cars[0] = new Monster;
	Cars[1] = new Monster2;
	printf("\n\n");
	Cars[0]->Born();
	Cars[1]->Born();
	printf("\n\n");
	for (int i = 0; i < 2; i++) {
		delete Cars[i];
	}
	return 0;
}