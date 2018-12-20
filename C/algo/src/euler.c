/***********************************************************
    euler.c -- ��ɮ��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NMAX    100                     /* ���ο��ξ�� */
#define EDGEMAX 100                     /* ���ο��ξ�� */
int adjacent[NMAX + 1][NMAX + 1];       /* ���ܹ��� */
int position[EDGEMAX + 1];
int n, n_edge, edge, solution;          /* ��, ���ο�; ��, ����ֹ� */

void readgraph(void)                    /* �ǡ������� */
{
    int i, j;

    if (scanf("%d%*[^\n]", &n) != 1 || n > NMAX) {  /* ���ο� */
        n = 0;  return;
    }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) adjacent[i][j] = 0;
    while (scanf("%d%d%*[^\n]", &i, &j) == 2) {
        n_edge++;                       /* ���ο� */
        adjacent[i][j]++;
        adjacent[j][i]++;               /* ͭ������դʤ餳�ιԤϺ�� */
    }
    printf("���ܹ���:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
        printf("\n");
    }
}

void visit(int i)
{
    int j;

    position[edge] = i;
    if (edge == n_edge) {
        printf("�� %d: ", ++solution);
        for (i = 0; i <= n_edge; i++) printf(" %d", position[i]);
        printf("\n");
    } else {
        for (j = 1; j <= n; j++) if (adjacent[i][j]) {
            adjacent[i][j]--;
            adjacent[j][i]--;  /* ͭ������դʤ餳�ιԤϺ�� */
            edge++;  visit(j);  edge--;
            adjacent[i][j]++;
            adjacent[j][i]++;  /* ͭ������դʤ餳�ιԤϺ�� */
        }
    }
}

int main()
{
    readgraph();                     /* �ǡ������ɤ� */
    solution = edge = 0;  visit(1);  /* ��1�����ȯ */
    if (solution == 0) printf("��ʤ�\n");
    return EXIT_SUCCESS;
}
