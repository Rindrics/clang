/**************************************************************
    bisect.c -- 2ʬˡ
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define samesign(x, y) (((x) > 0) == ((y) > 0))  /* Ʊ���ʤ鿿 */
double bisect(double a, double b, double tolerance,
        double (*f)(double), char **error)
{
    double c, fa, fb, fc;

    *error = NULL;
    if (tolerance < 0) tolerance = 0;
    if (b < a) {  c = a;  a = b;  b = c;  }
    fa = f(a);  if (fa == 0) return a;
    fb = f(b);  if (fb == 0) return b;
    if (samesign(fa, fb)) {
        *error = "��֤�ξü�Ǵؿ��ͤ�Ʊ���Ǥ�.";  return 0;
    }
    for ( ; ; ) {
        c = (a + b) / 2;
        if (c - a <= tolerance || b - c <= tolerance) break;
        fc = f(c);  if (fc == 0) return c;
        if (samesign(fc, fa)) {  a = c;  fa = fc;  }
        else                  {  b = c;  fb = fc;  }
    }
    return c;
}

double func(double x)  /* �����������ؿ����� */
{  return x * x - 2;  }

int main()  /* �ƥ��� */
{
    char *error;
    double x;

    x = bisect(1, 2, 0, func, &error);  /* $1 \le x \le 2$ �δ֤ǲ����� */
    if (error) printf("%s\n", error);
    else printf("x = % -24.16g\n", x);
    return EXIT_SUCCESS;
}
