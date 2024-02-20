#include <stdio.h>
#include <thread>

void thread1() { printf("thread1\n"); };
void thread2() { printf("thread2\n"); };
void thread3() { printf("thread3\n"); };

int main() {

	std::thread Th_1(thread1);
	Th_1.join();

	std::thread Th_2(thread2);
	Th_2.join();

	std::thread Th_3(thread3);
	Th_3.join();

	return 0;
}