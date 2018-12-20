/***********************************************************
    knight.c -- ���ν��������
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define N  5           /* ${\tt N} \times {\tt N}$ ������ */

int board[N + 4][N + 4],                /* ���� */
    dx[8] = { 2, 1,-1,-2,-2,-1, 1, 2 }, /* ���Ѱ� */
    dy[8] = { 1, 2, 2, 1,-1,-2,-2,-1 }; /* ���Ѱ� */

void printboard(void)                   /* ���̤���� */
{
    int i, j;
    static solution = 0;

    printf("\n�� %d\n", ++solution);
    for (i = 2; i <= N + 1; i++) {
        for (j = 2; j <= N + 1; j++) printf("%4d", board[i][j]);
        printf("\n");
    }
}

void try(int x, int y)  /* �Ƶ�Ū�˻�ߤ� */
{
    int i;
    static int count = 0;

    if (board[x][y] != 0) return;  /* ���Ǥ�ˬ�줿 */
    board[x][y] = ++count;
    if (count == N * N) printboard();  /* ���� */
    else for (i = 0; i < 8; i++) try(x + dx[i], y + dy[i]);
    board[x][y] = 0;  count--;
}

int main()
{
    int i, j;

    for (i = 0; i <= N + 3; i++)
        for (j = 0; j <= N + 3; j++) board[i][j] = 1;
    for (i = 2; i <= N + 1; i++)
        for (j = 2; j <= N + 1; j++) board[i][j] = 0;
    try(2, 2);
    return EXIT_SUCCESS;
}
