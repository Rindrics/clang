/***********************************************************
    meansd2.c -- ʿ���͡�ɸ���к�
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
        n++;  s1 += x;  s2 += x * x;
    }
    s1 /= n;                                  /* ʿ�� */
    s2 = (s2 - n * s1 * s1) / (n - 1);        /* ʬ�� */
    if (s2 > 0) s2 = sqrt(s2);  else s2 = 0;  /* ɸ���к� */
    printf("�Ŀ�: %d  ʿ��: %g  ɸ���к�: %g\n", n, s1, s2);
    return EXIT_SUCCESS;
}
