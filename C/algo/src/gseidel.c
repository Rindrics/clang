/***********************************************************
    gseidel.c -- Gauss (������)--Seidel (�����ǥ�) ˡ
***********************************************************/
#include "matutil.c"
#include <math.h>

#define VERBOSE   1     /* ����в����Ϥ��ʤ��ʤ� 0 �ˤ��� */
#define EPS       1E-6  /* ���Ƹ� */
#define MAX_ITER  500   /* ���緫�֤��� */

int gseidel(int n, matrix a, vector x, vector b)
{
    int j, i, ok, iter;
    double s;

    for (iter = 1; iter <= MAX_ITER; iter++) {
        ok = 1;
        for (i = 0; i < n; i++) {
            s = b[i];
            for (j = 0    ; j < i; j++) s -= a[i][j] * x[j];
            for (j = i + 1; j < n; j++) s -= a[i][j] * x[j];
            s /= a[i][i];  /* ���餫�����г���ʬ��1�ˤ��Ƥ��������� */
            if (ok && fabs(x[i] - s) > EPS * (1 + fabs(s)))
                ok = 0;
            x[i] = s;  /* SORˡ�ʤ��㤨�� x[i] += 1.2 * (s - x[i]); */
        }
        #if VERBOSE
            printf("%3d:\n", iter);
            vecprint(x, n, 7, "%11.6f");
        #endif
        if (ok) return EXIT_SUCCESS;  /* ���� */
    }
    return EXIT_FAILURE;  /* ��«���� */
}

int main()
{
    int i, j, n;
    matrix a;
    vector x, b;

    printf("n = ");  scanf("%d", &n);
    a = new_matrix(n, n);
    x = new_vector(n);  b = new_vector(n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) a[i][j] = 1;
        a[i][i] = 2;  b[i] = n + 1;  x[i] = 0;
    }
    if (gseidel(n, a, x, b) == EXIT_FAILURE)
        printf("��«���ޤ���\n");
    printf("�� (����Ϥ��٤� 1)\n");
    vecprint(x, n, 7, "%11.6f");
    return EXIT_SUCCESS;
}
