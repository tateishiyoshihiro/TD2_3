#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
#include<time.h>
//mac�Ƃ���Unix�nOS�̏ꍇ
//#include<Unistd.h>

typedef void (*PFunc)(int*);

//�R�[���o�b�N�֐�
void DispResult(int* s) {
	printf("%d�b�҂��Ď��s���ꂽ\n", *s);
}

void setTimeout(PFunc p, int second) {
	//�R�[���o�b�N�֐����Ăяo��
	Sleep(second * 1000);
	//mac�Ƃ���Unix�nOS�̏ꍇ
	//Sleep(second)
	p(&second);
}

int main() {
	
	//1.���I���ʂ̓����_���Ō��߂�
	unsigned int curretTime = time(nullptr); 
	srand(curretTime);

	//1~6�̗���
	int dice = rand() % 6 + 1;
	int result = dice % 2;
	//2.���[�U�������������̓��͂��󂯕t����
	int userAnswer = 0;
	printf("�����������\�z����A�����Ȃ�0��Ȃ�1�����\n");
	scanf_s("%d", &userAnswer);

	//3.
	printf("start\n");
	PFunc p;
	p = DispResult;
	setTimeout(p, 3);
	printf("鍎q�̏o�ڂ�%d�̂���\n", dice);
	printf("%d", result);
	if (result)
		printf("��\n");
	else
		printf("��\n");
	if (result == userAnswer)
		printf("����");
	else
		printf("�s����");
	return 0;
}