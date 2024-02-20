#include "Monster.h"
Monster::Monster() {
	name_ = "ƒSƒuƒŠƒ“";
	printf("%s‚ªŒ»‚ê‚½ \n", name_);
}
Monster::~Monster() {
	printf("%s‚Í“¦‚°‚½ \n", name_);
}
void Monster::Born() {
	printf("%s‚Í‚±‚ñ–_‚Å“Š‚°‚Á‚Ä‚«‚½ \n", name_);
}