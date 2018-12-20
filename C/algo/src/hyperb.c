/***********************************************************
    hyperb.c -- �ж����ؿ�
             -- ���ж����ؿ�
***********************************************************/
#include <math.h>
#define EPS5 0.001  /* DBL_EPSILON �� 1/5 ������ */

double my_sinh(double x)  /* ������ $\sinh x$ */
{
    double t;

    if (fabs(x) > EPS5) {
        t = exp(x);
        return (t - 1 / t) / 2;
    }
    return x * (1 + x * x / 6);
}

double my_cosh(double x)  /* ������ $\cosh x$ */
{
    double t;

    t = exp(x);
    return (t + 1 / t) / 2;
}

double my_tanh(double x)  /* ������ $\tanh x$ */
{
    if (x >  EPS5) return 2 / (1 + exp(-2 * x)) - 1;
    if (x < -EPS5) return 1 - 2 / (exp(2 * x) + 1);
    return x * (1 - x * x / 3);
}

double arcsinh(double x)  /* $\sinh^{-1} x$ */
{
    if (x >  EPS5) return  log(sqrt(x * x + 1) + x);
    if (x < -EPS5) return -log(sqrt(x * x + 1) - x);
    return x * (1 - x * x / 6);
}

double arccosh(double x)  /* $\cosh^{-1} x$, $x \ge 1$ */
{
    return log(x + sqrt(x * x - 1));
}

double arctanh(double x)  /* $\tanh^{-1} x$ */
{
    if (fabs(x) > EPS5)
        return 0.5 * log((1 + x) / (1 - x));
    return x * (1 + x * x / 3.0);
}

/************* �ʲ��ϥƥ����� **************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    double x;

    printf("�ж����ؿ��Ȥ��εդ�������\n");
    for (i = -10; i <= 10; i++)
        printf("%4d  % .3e  % .3e  % .3e\n",
            i, arcsinh(my_sinh(i)) - i,
               arccosh(my_cosh(i)) - fabs(i),
               arctanh(my_tanh(i)) - i);
    for (i = -10; i <= 10; i++) {
        x = 0.0002 * i;
        printf("%7.4f  % .3e  % .3e  % .3e\n",
            x, arcsinh(my_sinh(x)) - x,
               arccosh(my_cosh(x)) - fabs(x),
               arctanh(my_tanh(x)) - x);
    }
    printf("tanh �η夢�դ�ƥ��� (�饤�֥��ؿ������)\n");
    for (i = -5000; i <= 5000; i += 500)
        printf("%5d  % g % g\n", i, my_tanh(i), tanh(i));
    return EXIT_SUCCESS;
}
