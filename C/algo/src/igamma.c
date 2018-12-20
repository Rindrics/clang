/***********************************************************
    igamma.c -- �Դ�������޴ؿ�
***********************************************************/
#include <stdio.h>
#include <math.h>

/************ loggamma(x) -- gamma.c ���Ʒ� *************/

#define PI      3.14159265358979324  /* $\pi$ */
#define LOG_2PI 1.83787706640934548  /* $\log 2\pi$ */
#define N       8

#define B0  1                 /* �ʲ���Bernoulli�� */
#define B1  (-1.0 / 2.0)
#define B2  ( 1.0 / 6.0)
#define B4  (-1.0 / 30.0)
#define B6  ( 1.0 / 42.0)
#define B8  (-1.0 / 30.0)
#define B10 ( 5.0 / 66.0)
#define B12 (-691.0 / 2730.0)
#define B14 ( 7.0 / 6.0)
#define B16 (-3617.0 / 510.0)

double loggamma(double x)  /* ����޴ؿ����п� */
{
    double v, w;

    v = 1;
    while (x < N) {  v *= x;  x++;  }
    w = 1 / (x * x);
    return ((((((((B16 / (16 * 15))  * w + (B14 / (14 * 13))) * w
                + (B12 / (12 * 11))) * w + (B10 / (10 *  9))) * w
                + (B8  / ( 8 *  7))) * w + (B6  / ( 6 *  5))) * w
                + (B4  / ( 4 *  3))) * w + (B2  / ( 2 *  1))) / x
                + 0.5 * LOG_2PI - log(v) - x + (x - 0.5) * log(x);
}

/**********************************************************/

double q_gamma(double a, double x, double loggamma_a);
    /* �������. �ºݤ�����ϸ�. */

double p_gamma(double a, double x, double loggamma_a)  /* ��ʸ���� */
{
    int k;
    double result, term, previous;

    if (x >= 1 + a) return 1 - q_gamma(a, x, loggamma_a);
    if (x == 0)     return 0;
    result = term = exp(a * log(x) - x - loggamma_a) / a;
    for (k = 1; k < 1000; k++) {
        term *= x / (a + k);
        previous = result;  result += term;
        if (result == previous) return result;
    }
    printf("p_gamma(): ��«���ޤ���.\n");
    return result;
}

double q_gamma(double a, double x, double loggamma_a)  /* ��ʸ���� */
{
    int k;
    double result, w, temp, previous;
    double la = 1, lb = 1 + x - a;  /* Laguerre��¿�༰ */

    if (x < 1 + a) return 1 - p_gamma(a, x, loggamma_a);
    w = exp(a * log(x) - x - loggamma_a);
    result = w / lb;
    for (k = 2; k < 1000; k++) {
        temp = ((k - 1 - a) * (lb - la) + (k + x) * lb) / k;
        la = lb;  lb = temp;
        w *= (k - 1 - a) / k;
        temp = w / (la * lb);
        previous = result;  result += temp;
        if (result == previous) return result;
    }
    printf("q_gamma(): ��«���ޤ���.\n");
    return result;
}

double p_chisq(double chisq, int df)  /* ����2��ʬ�ۤβ�¦��Ψ */
{
    return p_gamma(0.5 * df, 0.5 * chisq, loggamma(0.5 * df));
}

double q_chisq(double chisq, int df)  /* ����2��ʬ�ۤξ�¦��Ψ */
{
    return q_gamma(0.5 * df, 0.5 * chisq, loggamma(0.5 * df));
}

#define LOG_PI 1.14472988584940017  /* $\log_e \pi$ */

double erf(double x)  /* Gauss�θ��ؿ� ${\rm erf}(x)$ */
{
    if (x >= 0) return   p_gamma(0.5, x * x, LOG_PI / 2);
    else        return - p_gamma(0.5, x * x, LOG_PI / 2);
}

double erfc(double x)  /* $1 - {\rm erf}(x)$ */
{
    if (x >= 0) return  q_gamma(0.5, x * x, LOG_PI / 2);
    else        return  1 + p_gamma(0.5, x * x, LOG_PI / 2);
}

double p_normal(double x)  /* ɸ������ʬ�ۤβ�¦��Ψ */
{
    if (x >= 0) return
        0.5 * (1 + p_gamma(0.5, 0.5 * x * x, LOG_PI / 2));
    else return
        0.5 * q_gamma(0.5, 0.5 * x * x, LOG_PI / 2);
}

double q_normal(double x)  /* ɸ������ʬ�ۤξ�¦��Ψ */
{
    if (x >= 0) return
        0.5 * q_gamma(0.5, 0.5 * x * x, LOG_PI / 2);
    else return
        0.5 * (1 + p_gamma(0.5, 0.5 * x * x, LOG_PI / 2));
}

#include <stdlib.h>

int main()  /* �ƥ��ȤΤ������� */
{
    int i;
    double x;

    printf("����ʬ�ۤξ�¦��Ψ�Υƥ���\n");
    for (i = 0; i <= 25; i++) {
        x = 0.2 * i;
        printf("%5.1f  %-25.17g\n", x, 1 - p_normal(x));
        printf("       %-25.17g\n", q_normal(x));
    }
    return EXIT_SUCCESS;
}
