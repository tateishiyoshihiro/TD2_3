#include "Monster.h"
Monster::Monster() {
	name_ = "�S�u����";
	printf("%s�����ꂽ \n", name_);
}
Monster::~Monster() {
	printf("%s�͓����� \n", name_);
}
void Monster::Born() {
	printf("%s�͂���_�œ������Ă��� \n", name_);
}