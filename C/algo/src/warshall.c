/***********************************************************
    warshall.c -- ���Ū����
    ������: warshall <warshall.dat
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NMAX 100                                /* ���ο��ξ�� */
char adjacent[NMAX + 1][NMAX + 1];              /* ���ܹ��� */

int n;                                          /* ���ο� */

void readgraph(void)                            /* �ǡ������� */
{
    int i, j;

    if (scanf("%d%*[^\n]", &n) != 1 || n > NMAX) {
        n = 0;  return;
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) adjacent[i][j] = 0;
        adjacent[i][i] = 1;
    }
    while (scanf("%d%d%*[^\n]", &i, &j) == 2)
        adjacent[i][j] = 1;
    printf("���ܹ���:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
        printf("\n");
    }
}

int main()
{
    int i, j, k;

    readgraph();
    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            if (adjacent[i][k])
                for (j = 1; j <= n; j++)
                    adjacent[i][j] |= adjacent[k][j];
    printf("���Ū����:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
        printf("\n");
    }
    return EXIT_SUCCESS;
}
