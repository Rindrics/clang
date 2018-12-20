/***********************************************************
    lu.c -- LUʬ��
***********************************************************/
#include "matutil.c"  /* �������ξ�ƻ�� */
#include <math.h>

double lu(int n, matrix a, int *ip)
{
    int i, j, k, ii, ik;
    double t, u, det;
    vector weight;

    weight = new_vector(n);    /* weight[0..n-1] �ε����ΰ���� */
    det = 0;                   /* ���� */
    for (k = 0; k < n; k++) {  /* �ƹԤˤĤ��� */
        ip[k] = k;             /* �Ը򴹾���ν���� */
        u = 0;                 /* ���ιԤ������ͺ�������Ǥ���� */
        for (j = 0; j < n; j++) {
            t = fabs(a[k][j]);  if (t > u) u = t;
        }
        if (u == 0) goto EXIT; /* 0 �ʤ�����LUʬ��Ǥ��ʤ� */
        weight[k] = 1 / u;     /* ���������ͤεտ� */
    }
    det = 1;                   /* ���󼰤ν���� */
    for (k = 0; k < n; k++) {  /* �ƹԤˤĤ��� */
        u = -1;
        for (i = k; i < n; i++) {  /* ��겼�γƹԤˤĤ��� */
            ii = ip[i];            /* �Ťߡ������� ������ιԤ򸫤Ĥ��� */
            t = fabs(a[ii][k]) * weight[ii];
            if (t > u) {  u = t;  j = i;  }
        }
        ik = ip[j];
        if (j != k) {
            ip[j] = ip[k];  ip[k] = ik;  /* ���ֹ��� */
            det = -det;  /* �Ԥ�򴹤���й��󼰤���椬�Ѥ�� */
        }
        u = a[ik][k];  det *= u;  /* �г���ʬ */
        if (u == 0) goto EXIT;    /* 0 �ʤ�����LUʬ��Ǥ��ʤ� */
        for (i = k + 1; i < n; i++) {  /* Gauss�õ�ˡ */
            ii = ip[i];
            t = (a[ii][k] /= u);
            for (j = k + 1; j < n; j++)
                a[ii][j] -= t * a[ik][j];
        }
    }
EXIT:
    free_vector(weight);  /* �����ΰ����� */
    return det;           /* ����ͤϹ��� */
}

void solve(int n, matrix a, vector b, int *ip, vector x)
{
    int i, j, ii;
    double t;

    for (i = 0; i < n; i++) {       /* Gauss�õ�ˡ�λĤ� */
        ii = ip[i];  t = b[ii];
        for (j = 0; j < i; j++) t -= a[ii][j] * x[j];
        x[i] = t;
    }
    for (i = n - 1; i >= 0; i--) {  /* �������� */
        t = x[i];  ii = ip[i];
        for (j = i + 1; j < n; j++) t -= a[ii][j] * x[j];
        x[i] = t / a[ii][i];
    }
}

double gauss(int n, matrix a, vector b, vector x)
{
    double det;  /* ���� */
    int *ip;     /* �Ը򴹤ξ��� */

    ip = malloc(sizeof(int) * n);         /* �����ΰ���� */
    if (ip == NULL) error("�����ΰ���­");
    det = lu(n, a, ip);                   /* LUʬ�� */
    if (det != 0) solve(n, a, b, ip, x);  /* LUʬ��η�̤�Ȥä�ϢΩ��������� */
    free(ip);                             /* �����ΰ�β��� */
    return det;                           /* ����ͤϹ��� */
}

/********** �ʲ��ϥƥ����� **********/

#include <limits.h>

double rnd(void)  /* ���  0 < rnd() < 1 */
{
    static unsigned long seed = 123456789UL;  /* ��� */

    return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main()
{
    int i, j, n;
    matrix a, asave;
    vector b, bsave, x;
    double s, det;

    printf("n = ");  scanf("%d", &n);  /* ����μ��������� */
    a = new_matrix(n, n);  asave = new_matrix(n, n);
    b = new_vector(n);  bsave = new_vector(n);
    x = new_vector(n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            a[i][j] = asave[i][j] = rnd() - rnd();
    printf("��������\n");  matprint(a, n, 10, "%7.3f");
    for (i = 0; i < n; i++)
        b[i] = bsave[i] = rnd() - rnd();
    printf("����\n");  vecprint(b, n, 10, "%7.3f");
    det = gauss(n, a, b, x);  /* Gaussˡ�� $Ax=b$ ��� */
    printf("���� = %g\n", det);
    printf("���, ������������Ȥ���ξ�դκ�\n");
    for (i = 0; i < n; i++) {
        s = bsave[i];
        for (j = 0; j < n; j++) s -= asave[i][j] * x[j];
        printf("%4d: %12.7f %12.7f\n", i, x[i], s);
    }
    return EXIT_SUCCESS;
}
