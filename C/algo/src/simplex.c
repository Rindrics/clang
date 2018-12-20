/***********************************************************
    simplex.c -- �����ײ�ˡ
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define EPS     1E-6    /* ̵�¾� */
#define LARGE   1E+30   /* ̵���� */
#define MMAX    20      /* �� (���) �ο��ξ�� */
#define NMAX    100     /* �� (�ѿ�) �ο��ξ�� */

float a[MMAX + 1][NMAX + 1],    /* ��Ｐ�η��� */
      c[NMAX + 1],              /* ��Ū�ؿ��η��� */
      q[MMAX + 1][MMAX + 1],    /* �Ѵ����� */
      pivotcolumn[MMAX + 1];    /* �ԥܥå��� */
int m, n,       /* �� (���), �� (�ѿ�) �ο� */
    n1,         /* {\tt n} $+$ ��Υ���å��ѿ��ο� */
    n2,         /* {\tt n1} $+$ ���Υ���å��ѿ��ο� */
    n3,         /* {\tt n2} $+$ �Ͱ��ѿ��ο� */
    jmax,       /* �Ǳ�����ֹ� */
    col[MMAX + 1],  /* �ƹԤδ����ѿ����ֹ� */
    row[NMAX + 2*MMAX + 1],
                /* �����󤬴���ʤ��б���������ֹ�, �����Ǥʤ����0 */
    nonzero_row[NMAX + 2*MMAX + 1]; /* ����å����Ͱ��ѿ���0�Ǥʤ��� */
char inequality[MMAX + 1];  /*  <, >, =  */

void error(char *message)  /* ���顼ɽ��, ��λ */
{
    fprintf(stderr, "\n%s\n", message);  exit(EXIT_FAILURE);
}

double getnum(void)  /* �¿���ɸ�����Ϥ����ɤ� */
{
    int r;
    double x;

    while ((r = scanf("%lf", &x)) != 1) {
        if (r == EOF) error("���ϥ��顼");
        scanf("%*[^\n]");  /* ���顼�����Τ�������ޤ��ɤ����Ф� */
    }
    return x;
}

void readdata(void)  /* �ǡ������ɤ� */
{
    int i, j;
    char s[2];

    m = (int)getnum();  n = (int)getnum();
    if (m < 1 || m > MMAX || n < 1 || n > NMAX)
        error("���ο� m �ޤ����ѿ��ο� n ���ϰϳ��Ǥ�");
    for (j = 1; j <= n; j++) c[j] = getnum();
    c[0] = -getnum();  /* {\tt c[0]}������դˤ��� */
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) a[i][j] = getnum();
        if (scanf(" %1[><=]", s) != 1) error("���ϥ��顼");
        inequality[i] = s[0];
        a[i][0] = getnum();
        if (a[i][0] < 0) {
            if      (inequality[i] == '>') inequality[i] = '<';
            else if (inequality[i] == '<') inequality[i] = '>';
            for (j = 0; j <= n; j++) a[i][j] = -a[i][j];
        } else if (a[i][0] == 0 && inequality[i] == '>') {
            inequality[i] = '<';
            for (j = 1; j <= n; j++) a[i][j] = -a[i][j];
        }
    }
}

void prepare(void)  /* ���� */
{
    int i;

    n1 = n;
    for (i = 1; i <= m; i++)
        if (inequality[i] == '>') {  /* ������$-1$�Υ���å��ѿ� */
            n1++;  nonzero_row[n1] = i;
        }
    n2 = n1;
    for (i = 1; i <= m; i++)
        if (inequality[i] == '<') {  /* ������$+1$�Υ���å��ѿ� */
            n2++;  col[i] = n2;
            nonzero_row[n2] = row[n2] = i;
        }
    n3 = n2;
    for (i = 1; i <= m; i++)
        if (inequality[i] != '<') {  /* �Ͱ��ѿ� */
            n3++;  col[i] = n3;
            nonzero_row[n3] = row[n3] = i;
        }
    for (i = 0; i <= m; i++) q[i][i] = 1;
}

double tableau(int i, int j)
{
    int k;
    double s;

    if (col[i] < 0) return 0;  /* �ä����� */
    if (j <= n) {
        s = 0;
        for (k = 0; k <= m; k++) s += q[i][k] * a[k][j];
        return s;
    }
    s = q[i][nonzero_row[j]];
    if (j <= n1) return -s;
    if (j <= n2 || i != 0) return s;
    return s + 1;  /* j > n2 && i == 0 */
}

void writetableau(int ipivot, int jpivot)
    /* �ǥ�󥹥ȥ졼�����Τ��᥷��ץ�å���ɽ����� */
{
    int i, j;

    for (i = 0; i <= m; i++)
        if (col[i] >= 0) {
            printf("%2d: ", i);
            for (j = 0; j <= jmax; j++)
                printf("%7.2f%c", tableau(i, j),
                    (i == ipivot && j == jpivot) ? '*' : ' ');
            printf("\n");
        }
}

void pivot(int ipivot, int jpivot)  /* �ݤ��Ф� */
{
    int i, j;
    double u;

    printf("�ԥܥåȰ��� (%d, %d)\n", ipivot, jpivot);
    u = pivotcolumn[ipivot];
    for (j = 1; j <= m; j++) q[ipivot][j] /= u;
    for (i = 0; i <= m; i++)
        if (i != ipivot) {
            u = pivotcolumn[i];
            for (j = 1; j <= m; j++)
                q[i][j] -= q[ipivot][j] * u;
        }
    row[col[ipivot]] = 0;
    col[ipivot] = jpivot;  row[jpivot] = ipivot;
}

void minimize(void)  /* �Ǿ��� */
{
    int i, ipivot, jpivot;
    double t, u;

    for ( ; ; ) {
        /* �ԥܥå��� jpivot �򸫤Ĥ��� */
        for (jpivot = 1; jpivot <= jmax; jpivot++)
            if (row[jpivot] == 0) {
                pivotcolumn[0] = tableau(0, jpivot);
                if (pivotcolumn[0] < -EPS) break;
            }
        if (jpivot > jmax) break;  /* �Ǿ�����λ */
        /* �ԥܥåȹ� ipivot �򸫤Ĥ��� */
        u = LARGE;  ipivot = 0;
        for (i = 1; i <= m; i++) {
            pivotcolumn[i] = tableau(i, jpivot);
            if (pivotcolumn[i] > EPS) {
                t = tableau(i, 0) / pivotcolumn[i];
                if (t < u) {  ipivot = i;  u = t;  }
            }
        }
        if (ipivot == 0) {
            printf("��Ū�ؿ��ϲ��¤�����ޤ���\n");
            exit(EXIT_SUCCESS);
        }
        writetableau(ipivot, jpivot);
        pivot(ipivot, jpivot);
    }
    writetableau(-1, -1);
    printf("�Ǿ��ͤ� %g �Ǥ�\n", -tableau(0, 0));
}

void phase1(void)  /* �ե������� */
{
    int i, j;
    double u;

    printf("�ե�������\n");
    jmax = n3;
    for (i = 0; i <= m; i++)
        if (col[i] > n2) q[0][i] = -1;
    minimize();
    if (tableau(0, 0) < -EPS) {
        printf("��ǽ�ʲ�Ϥ���ޤ���\n");
        exit(EXIT_SUCCESS);
    }
    for (i = 1; i <= m; i++)
        if (col[i] > n2) {
            printf("��� %d �Ͼ�Ĺ�Ǥ�\n", i);
            col[i] = -1;
        }
    q[0][0] = 1;
    for (j = 1; j <= m; j++) q[0][j] = 0;
    for (i = 1; i <= m; i++)
        if ((j = col[i]) > 0 && j <= n && (u = c[j]) != 0)
            for (j = 1; j <= m; j++)
                q[0][j] -= q[i][j] * u;
}

void phase2(void)
{
    int j;

    printf("�ե�������\n");  jmax = n2;
    for (j = 0; j <= n; j++) a[0][j] = c[j];  /* ��Ū�ؿ� */
    minimize();
}

void report(void)  /* ��̤ν��� */
{
    int i, j;

    printf("0 �Ǥʤ��ѿ�����:\n");
    for (j = 1; j <= n; j++)
        if ((i = row[j]) != 0)
            printf("x[%d] = %g\n", j, tableau(i, 0));
}

int main()
{
    readdata();                 /* �ǡ������ɤ� */
    prepare();                  /* �������館 */
    if (n3 != n2) phase1();     /* �ե�����1 */
    phase2();                   /* �ե�����2 */
    report();                   /* ��̤ν��� */
    return EXIT_SUCCESS;
}
