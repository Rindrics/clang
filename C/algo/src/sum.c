/***********************************************************
    sum.c -- �������
***********************************************************/

float sum1(int n, float a[])  /* �̾����ˡ */
{
    int i;
    float s;

    s = 0;
    for (i = 0; i < n; i++) s += a[i];
    return s;
}

float sum2(int n, float a[])  /* ��������к� */
{
    int i;
    float r, s, t;

    r = 0;  s = 0;    /* s ����, r ���Ѥ߻Ĥ� */
    for (i = 0; i < n; i++) {
        r += a[i];    /* �Ѥ߻Ĥ� + �ä������� */
        t = s;        /* ����ޤǤ��� */
        s += r;       /* �¤򹹿� */
        t -= s;       /* �ºݤ��Ѥޤ줿�ͤ������Ѥ������ */
        r += t;       /* �Ѥ߻Ĥ� */
    }
    return s;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    static float a[10001];

    printf("1 + 0.0001 + ... + 0.0001 = 2\n");
    a[0] = 1;
    for (i = 1; i <= 10000; i++) a[i] = 0.0001;
    printf("��ˡ1: %.6f\n", sum1(10001, a));
    printf("��ˡ2: %.6f\n", sum2(10001, a));
    return EXIT_SUCCESS;
}
