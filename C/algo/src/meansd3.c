/***********************************************************
    meansd3.c -- ʿ���͡�ɸ���к�
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n;
    float x, s1, s2;

    s1 = s2 = n = 0;
    while (scanf("%f", &x) == 1) {
        n++;                        /* �Ŀ� */
        x -= s1;                    /* ��ʿ�ѤȤκ� */
        s1 += x / n;                /* ʿ�� */
        s2 += (n - 1) * x * x / n;  /* ʿ���� */
    }
    s2 = sqrt(s2 / (n - 1));  /* ɸ���к� */
    printf("�Ŀ�: %d  ʿ��: %g  ɸ���к�: %g\n", n, s1, s2);
    return EXIT_SUCCESS;
}
