#include <stdio.h>
int Recursive(int n, int m) {
	if (n <= 1) {
		return m;
	}
	return (m + Recursive(n - 1, m * 2 - 50));
}
int main() {
	int n = 8;//�K�悷��l(����������)
	int result;//�v�Z����
	int num = 1072;
	num = num * n;
	result = Recursive(n,100);
	printf("%d���ԓ��������̒����i�ċA�I�j=%d�~\n", n, result);
	printf("%d���ԓ��������̒����i��ʓI�j=%d�~\n", n, num);
	return (0);
}