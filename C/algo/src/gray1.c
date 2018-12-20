/***********************************************************
    gray1.c -- Gray (���쥤) ���
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define N  6  /* ��� */

int main()
{
    int i;
    char binary[N + 1], Gray[N];

    for (i = 0; i < N; i++) binary[i] = Gray[i] = 0;
    binary[N] = 0;  /* �ֿ� */
    printf("%*s  %*s\n", N, "binary", N, "Gray");
    for ( ; ; ) {
        /* ����. */
        for (i = N - 1; i >= 0; i--) printf("%d", binary[i]);
        printf("  ");
        for (i = N - 1; i >= 0; i--) printf("%d", Gray[i]);
        printf("\n");
        for (i = 0; binary[i] == 1; i++) binary[i] = 0;
        if (i == N) break;
        binary[i] = 1;
        Gray[i] ^= 1;  /* 1���Ѥ�������Ǽ���Gray��椬������. */
    }
    return EXIT_SUCCESS;
}
