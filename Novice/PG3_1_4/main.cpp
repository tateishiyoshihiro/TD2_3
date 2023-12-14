#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include <functional>

typedef void (*PFunc)(int*);

// コールバック関数
void DispResult(int* s) { printf("%d秒待って実行された\n", *s); }

//void setTimeout(PFunc p, int second) {
//	// コールバック関数を呼び出す
//	Sleep(second * 1000);
//	// macとかのUnix系OSの場合
//	// Sleep(second)
//	p(&second);
//}

int main(int argc, const char* argv[]) { 
	int num = 10;
	std::function<void(int)> 
		setTimeout = [](int second,PFunc p) { 
		// コールバック関数を呼び出す };
		Sleep(second * 1000);
		// macとかのUnix系OSの場合
		// Sleep(second)
		p(&second);

	
	// 1.抽選結果はランダムで決める
	unsigned int curretTime = time(nullptr);
	srand(curretTime);

	// 1~6の乱数
	int dice = rand() % 6 + 1;
	int result = dice % 2;
	// 2.ユーザから奇数か偶数かの入力を受け付ける
	int userAnswer = 0;
	printf("奇数か偶数かを予想する、偶数なら0奇数なら1を入力\n");
	scanf_s("%d", &userAnswer);

	// 3.
	printf("start\n");
	PFunc p;
	p = DispResult;
	setTimeout(p, 3);
	printf("骰子の出目が%dのため\n", dice);
	printf("%d", result);
	if (result)
		printf("半\n");
	else
		printf("丁\n");
	if (result == userAnswer)
		printf("正解");
	else
		printf("不正解");
	return 0;
}