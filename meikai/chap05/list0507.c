/*
	�z��̗v�f�ɒl��ǂݍ���ŕ\��
*/

#include <stdio.h>

int main(void)
{
	int i;
	int x[5];

	for (i = 0; i < 5; i++) {	/* �v�f�ɒl��ǂݍ��� */
		printf("x[%d] : ", i);
		scanf("%d", &x[i]);
	}

	for (i = 0; i < 5; i++)		/* �v�f�̒l��\�� */
		printf("x[%d] = %d\n", i, x[i]);

	return 0;
}