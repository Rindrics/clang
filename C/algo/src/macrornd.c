/***********************************************************
    macrornd.c -- ������Ʊˡ
***********************************************************/
/* C����Υޥ���Ǽ¸�������ñ��������Ʊˡ���. */

#include <limits.h>
static unsigned long seed = 1;  /* ��� */
#define rnd() (seed *= 69069UL, seed / (ULONG_MAX + 1.0))
#define init_rnd(x) (seed = (unsigned long)(x) | 1)

/************ �ʲ��ϥƥ����� *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    unsigned long i, n;
    double r, s1, s2, x, x0, xprev;

    printf("����μ�? ");  scanf("%lu", &i);
    init_rnd(i);  /* Ǥ�դ� unsigned long �ǽ����. */
    printf("�Ŀ�? ");  scanf("%lu", &n);

    s1 = x0 = xprev = rnd() - 0.5;  s2 = x0 * x0;  r = 0;
    for (i = 1; i < n; i++) {
        x = rnd() - 0.5;
        s1 += x;  s2 += x * x;  r += xprev * x;  xprev = x;
    }
    r = (n * (r + x * x0) - s1 * s1) / (n * s2 - s1 * s1);

    printf("�ʲ��ϴ����ͤȤκ���ɸ����ǳ�ä����.\n");
    printf("20����19��ϡ�2���������Ϥ�.\n");
    printf("ʿ���͡ġġġġġ� %6.3f\n", s1 * sqrt(12.0 / n));
    printf("��Ʊ�Τ���ط����� %6.3f\n",
        ((n - 1) * r + 1) * sqrt((n + 1.0) / (n * (n - 3.0))));

    return EXIT_SUCCESS;
}
