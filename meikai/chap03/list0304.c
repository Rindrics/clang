/*
	�ǂݍ��񂾐����l�͊�ł��邩�����ł��邩
*/

#include <stdio.h>

int main(void)
{
	int no;

	printf("��������͂��Ă��������F");
	scanf("%d", &no);

	if (no % 2)
		puts("���̐��͊�ł��B");
	else
		puts("���̐��͋����ł��B");

	return 0;
}