/***********************************************************
    dfs.c -- �ķ�õ��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define NMAX 100                                /* ���ο��ξ�� */
char adjacent[NMAX + 1][NMAX + 1];              /* ���ܹ��� */

int n = 7;                                      /* ���ο� (��) */
int data[] = { 1, 2, 2, 3, 1, 3, 2, 4, 5, 7 };  /* �ǡ��� (��) */

void readgraph(void)  /* ��������� */
{
    int i, j, k;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) adjacent[i][j] = 0;
    for (k = 0; k < (sizeof data) / (sizeof *data); k++) {
        if (k % 2 == 0) i = data[k];
        else {
            j = data[k];
            adjacent[i][j] = adjacent[j][i] = 1;
        }
    }
    printf("���ܹ���:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
        printf("\n");
    }
}

char visited[NMAX + 1];  /* ˬ�줿�ʤ�1 */

void visit(int i)  /* �� {\tt i} ��ˬ��� (�Ƶ�Ū) */
{
    int j;

    printf(" %d", i);  visited[i] = 1;
    for (j = 1; j <= n; j++)
        if (adjacent[i][j] && ! visited[j]) visit(j);
}

int main()
{
    int i, count;

    readgraph();                              /* ����դΥǡ������ɤ� */
    for (i = 1; i <= n; i++) visited[i] = 0;  /* �ޤ��ɤ���ˬ��Ƥ��ʤ� */
    printf("Ϣ����ʬ:\n");
    count = 0;                                /* Ϣ����ʬ������� */
    for (i = 1; i <= n; i++)
        if (! visited[i]) {
            printf("%3d:", ++count);
            visit(i);  printf("\n");
        }
    return EXIT_SUCCESS;
}
