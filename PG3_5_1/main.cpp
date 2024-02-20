#include <iostream>
#include <list>
#include <stdio.h>

using namespace std;

int main() {

	list<const char*> list_{ "Tokyo",     "Kanda",    "Akihabara",    "Okachimachi", "Uguisudani",
							"Nippori",   "Tabata",   "Komagome",     "Sugamo",      "Otsuka",
							"Ikebukuro", "Mejiro",   "Takadanobaba", "Shin-Okubo",  "Shinjuku",
							"Yoyogi",    "Harajuku", "Shibuya",      "Ebisu",       "Meguro",
							"Gotanda",   "Osaki",    "Sinagawa",     "Tamachi",     "Hamamatsucho",
							"Shimbasi",  "Yurakucho" };

	printf("1970”N‰wˆê——\n");

	for (list<const char*>::iterator mt_ = list_.begin(); mt_ != list_.end(); ++mt_) {
		cout << *mt_ << endl;
	}

	printf("\n");

	printf("2019”N‰wˆê——\n");

	for (list<const char*>::iterator mt_1 = list_.begin(); mt_1 != list_.end(); ++mt_1) {
		if (*mt_1 == "Tabata") {
			mt_1 = list_.insert(mt_1, "Nishi-Nippori");

			++mt_1;
		}
	}

	for (list<const char*>::iterator it_f = list_.begin(); it_f != list_.end(); ++it_f) {
		cout << *it_f << endl;
	}

	printf("\n");

	printf("2022”N‰wˆê——\n");

	for (list<const char*>::iterator it_f = list_.begin(); it_f != list_.end(); ++it_f) {
		if (*it_f == "Tamachi") {
			it_f = list_.insert(it_f, "Takanawa Gateway");

			++it_f;
		}
	}

	for (list<const char*>::iterator it_f = list_.begin(); it_f != list_.end(); ++it_f) {
		cout << *it_f << endl;
	}

	return 0;
}