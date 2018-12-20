/***********************************************************
    irandom.c -- ����ʬ��
              -- 2��ʬ��
              -- Poisson (�ݥ�����) ʬ��
***********************************************************/

/***** ������� (������Ʊˡ) ******************************/

#include <limits.h>
static unsigned long seed = 1;  /* Ǥ�� */

void init_rnd(unsigned long x)
{
    seed = x;
}

unsigned long irnd(void)
{
    seed = seed * 1566083941UL + 1;
    return seed;
}

double rnd(void)  /* 0 <= rnd() < 1 */
{
    return (1.0 / (ULONG_MAX + 1.0)) * irnd();
}

/**********************************************************/

#include <math.h>

int geometric_rnd1(double p)  /* ����ʬ�� 1 */
{
    int n;

    n = 1;
    while (rnd() > p) n++;
    return n;
}

int geometric_rnd(double p)  /* ����ʬ�� 2 */
{
    return ceil(log(1 - rnd()) / log(1 - p));
}

int binomial_rnd(int n, double p)  /* 2��ʬ�� */
{
    int i, r;

    r = 0;
    for (i = 0; i < n; i++)
        if (rnd() < p) r++;
    return r;
}

int Poisson_rnd(double lambda)  /* Poisson (�ݥ�����) ʬ�� */
{
    int k;

    lambda = exp(lambda) * rnd();
    k = 0;
    while (lambda > 1) {
        lambda *= rnd();  k++;
    }
    return k;
}

/**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i, choice, x, n, histo[20];
    double a, b, s1, s2;

    init_rnd((unsigned long) time(NULL));  /* ����� */

    printf("***** ��˥塼 *****\n");
    printf("  1: ����ʬ�� 1\n");
    printf("  2: ����ʬ�� 2\n");
    printf("  3: ����ʬ��\n");
    printf("  4: �ݥ�����ʬ��\n");
    printf("? ");  scanf("%d", &choice);

    switch(choice) {
    case 1: case 2: case 4:
        printf("���� (1��)? ");  scanf("%lf", &a);  break;
    case 3:
        printf("���� (2��)? ");  scanf("%lf%lf", &a, &b);  break;
    }
    printf("�Ŀ�? ");  scanf("%d", &n);

    for (i = 0; i < 20; i++) histo[i] = 0;
    s1 = s2 = 0;
    for (i = 0; i < n; i++) {
        switch(choice) {
        case 1: x = geometric_rnd1(a);  break;
        case 2: x = geometric_rnd(a);  break;
        case 3: x = binomial_rnd(a, b);  break;
        case 4: x = Poisson_rnd(a);  break;
        }
        if (x >= 0 && x < 20) histo[x]++;
        s1 += x;  s2 += x * x;
    }

    for (i = 0; i < 20; i++)
        printf("%4d: %5.1f%%\n", i, 100.0 * histo[i] / n);
    s1 /= n;  s2 = sqrt((s2 - n * s1 * s1) / (n - 1));
    printf("ʿ�� %g  ɸ���к� %g\n", s1, s2);

    return EXIT_SUCCESS;
}
