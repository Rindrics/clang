/***********************************************************
    meansd1.c -- ʿ���͡�ɸ���к�
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NMAX 1000

int main()
{
    int i, n;
    float x, s1, s2;
    static float a[NMAX];

    s1 = s2 = n = 0;
    while (scanf("%f", &x) == 1) {
        if (n >= NMAX) return EXIT_FAILURE;
        a[n++] = x;  s1 += x;
    }
    s1 /= n; /* ʿ�� */
    for (i = 0; i < n; i++) {
        x = a[i] - s1;  s2 += x * x;
    }
    s2 = sqrt(s2 / (n - 1));  /* ɸ���к� */
    printf("�Ŀ�: %d  ʿ��: %g  ɸ���к�: %g\n", n, s1, s2);
    return EXIT_SUCCESS;
}
