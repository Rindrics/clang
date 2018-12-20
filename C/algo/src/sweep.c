/***********************************************************
    sweep.c -- SWEEP�黻��ˡ
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define SCALAR double   /* ������­�ʤ� float �� */
#include "statutil.c"   /* ¿���̥ǡ������ϥ롼���� */

int n, m, ndf;          /* �ǡ����η��, �ѿ��ο�, ��ͳ�� */
char *added;            /* �����ѿ��˺��Ѥ����� */
matrix a;               /* ���¹��� */

void sweep(int k)  /* �ݤ��Ф��黻 */
{
    int i, j;
    double b, d;

    if ((d = a[k][k]) == 0) {
        printf("�ѿ� %d: �켡��°.\n", k);  return;
    }
    for (j = 0; j <= m; j++) a[k][j] /= d;
    for (j = 0; j <= m; j++) {
        if (j == k) continue;
        b = a[j][k];
        for (i = 0; i <= m; i++) a[j][i] -= b * a[k][i];
        a[j][k] = -b / d;
    }
    a[k][k] = 1 / d;
    if (added[k]) {  added[k] = 0;  ndf++;  }
    else          {  added[k] = 1;  ndf--;  }
}

void regress(int k)  /* ����ѿ� k �ˤĤ��Ʋ󵢷����ʤɤ���� */
{
    int j;
    double s, rms;

    if (added[k]) {  printf("???\n");  return;  }
    rms = (ndf > 0 && a[k][k] >= 0) ? sqrt(a[k][k] / ndf) : 0;
    printf("�ѿ�  �󵢷���       ɸ���        t\n");
    for (j = 0; j <= m; j++) {
        if (! added[j]) continue;
        s = (a[j][j] >= 0) ? sqrt(a[j][j]) * rms : 0;
        printf("%4d  % #-14g % #-14g", j, a[j][k], s);
            if (s > 0) printf("  % #-11.3g", fabs(a[j][k] / s));
        printf("\n");
    }
    printf("����ѿ�: %d  �ĺ�2����: %g  ��ͳ��: %d  "
           "�ĺ�RMS: %g\n", k, a[k][k], ndf, rms);
}

void residuals(void)  /* �ĺ������¹������� */
{
    int i, j, k;

    for (i = 0; i <= m; i += 5) {
        for (k = i; k < i + 5 && k <= m; k++)
            printf("      %-8d", k);
        printf("\n");
        for (j = 0; j <= m; j++) {
            printf("%4d  ", j);
            for (k = i; k < i + 5 && k <= m; k++)
                printf("% -14g", a[j][k]);
            printf("\n");
        }
    }
}

int main(int argc, char *argv[])
{
    int i, j, k, c;
    FILE *datafile;
    vector x;

    printf("********** ���÷���ʬ�� **********\n\n");
    if (argc != 2) error("����ˡ: reg datafile");
    datafile = fopen(argv[1], "r");
    if (datafile == NULL) error("�ե����뤬�ɤ�ޤ���.");
    n = ndf = getnum(datafile);  m = getnum(datafile);
    printf("%d �� �� %d �ѿ�\n", n, m);
    if (n < 1 || m < 1) error("�ǡ�������");
    if ((added = malloc(m + 1)) == NULL
     || (a = newmat(m + 1, m + 1)) == NULL
     || (x = newvec(m + 1)) == NULL) error("�����ΰ���­");
    for (j = 0; j <= m; j++) {
        added[j] = 0;
        for (k = j; k <= m; k++) a[j][k] = 0;
    }
    for (i = 0; i < n; i++) {
        printf(".");  x[0] = 1;
        for (j = 1; j <= m; j++) {
            x[j] = getnum(datafile);
            if (missing(x[j])) error("�ǡ�������");
        }
        for (j = 0; j <= m; j++)
            for (k = j; k <= m; k++) a[j][k] += x[j] * x[k];
    }
    printf("\n");  fclose(datafile);
    for (j = 0; j <= m; j++)
        for (k = 0; k < j; k++) a[j][k] = a[k][j];
    c = '\n';
    do {
        if (c == 'X' || c == 'Y')
            if (scanf("%d", &j) != 1 || j < 0 || j > m)
                c = '\0';
        switch (c) {
        case 'X':  sweep(j);  break;
        case 'Y':  regress(j);  break;
        case 'R':  residuals();  break;
        case '\n': printf("̿��(Xj/Yj/R/Q)? ");
                   break;
        default:   printf("???\n");  break;
        }
    } while ((c = toupper(getchar())) != EOF && c != 'Q');
    return EXIT_SUCCESS;
}
