#include <stdio.h>
int Recursive(int n, int m) {
	if (n <= 1) {
		return m;
	}
	return (m + Recursive(n - 1, m * 2 - 50));
}
int main() {
	int n = 8;//階乗する値(働いた時間)
	int result;//計算結果
	int num = 1072;
	num = num * n;
	result = Recursive(n,100);
	printf("%d時間働いた時の賃金（再帰的）=%d円\n", n, result);
	printf("%d時間働いた時の賃金（一般的）=%d円\n", n, num);
	return (0);
}