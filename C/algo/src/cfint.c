/***********************************************************
    cfint.c -- Ϣʬ�����
***********************************************************/
#define N  5          /* ���ο� */
double x[N], y[N];    /* N �Ĥ����� x ��ɸ, y ��ɸ */

void maketable(void)  /* �������� y[] �˾�� */
{
    int i, j;

    for (j = 0; j < N - 1; j++)
        for (i = j + 1; i < N; i++)
            y[i] = (x[i] - x[j]) / (y[i] - y[j]);
}

double interpolate(double t)  /* ��� */
{
    int i;
    double r;

    r = y[N - 1];
    for (i = N - 2; i >= 0; i--) r = (t - x[i]) / r + y[i];
    return r;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846264

int main()
{
    int i;
    double s;

    for (i = 0; i < N; i++) {           /* ɽ���� */
        x[i] = 20 * i;  y[i] = tan(x[i] * PI / 180);
    }
    maketable();
    for (i = 0; i <= 80; i += 2) {      /* ��� */
        s = interpolate(i);
        printf("%2d  % .14f  % .2e\n",
            i, s, s - tan(i * PI / 180));
    }
    return EXIT_SUCCESS;
}
