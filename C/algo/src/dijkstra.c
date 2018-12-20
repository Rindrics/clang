/***********************************************************
    dijkstra.c -- ��ûϩ����
    ������: dijkstra <dijkstra.dat
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NMAX 100                 /* ���ο��ξ�� */
int weight[NMAX + 1][NMAX + 1];  /* �դνŤ� */
int n;                           /* ���ο� */

void readweight(void)            /* �ǡ������� */
{
    int i, j, x;

    if (scanf("%d%*[^\n]", &n) != 1 || n > NMAX) {
        n = 0;  return;
    }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) weight[i][j] = INT_MAX;
    while (scanf("%d%d%d%*[^\n]", &i, &j, &x) == 3)
        weight[i][j] = weight[j][i] = x;
    printf("�ǡ��� weight(i,j)\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (weight[i][j] < INT_MAX)
                printf("%3d", weight[i][j]);
            else
                printf(" ��");
        }
        printf("\n");
    }
}

#define START  1  /* ��ȯ�� */
#define FALSE  0
#define TRUE   1

int main()
{
    int i, j, next, min;
    static char visited[NMAX + 1];
    static int distance[NMAX + 1], prev[NMAX + 1];

    readweight();  /* ���ο�{\tt n}, ��Υ{\tt weight[1..n][1..n]}���ɤ� */
    for (i = 1; i <= n; i++) {
        visited[i] = FALSE;  distance[i] = INT_MAX;
    }
    distance[START] = 0;  next = START;
    do {
        i = next;  visited[i] = TRUE;  min = INT_MAX;
        for (j = 1; j <= n; j++) {
            if (visited[j]) continue;
            if (weight[i][j] < INT_MAX &&
                    distance[i] + weight[i][j] < distance[j]) {
                distance[j] = distance[i] + weight[i][j];
                prev[j] = i;
            }
            if (distance[j] < min) {
                min = distance[j];  next = j;
            }
        }
    } while (min < INT_MAX);
    printf("��  ľ������  ��û��Υ\n");
    for (i = 1; i <= n; i++)
        if (i != START && visited[i])
            printf("%2d%10d%10d\n", i, prev[i], distance[i]);
    return EXIT_SUCCESS;
}
