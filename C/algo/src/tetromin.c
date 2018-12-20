/***********************************************************
    tetromin.c -- �ƥȥ�ߥΤ�Ȣ�ͤ�ѥ���
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define Pieces      5  /* ��ο� */
#define Col         5  /* �פ�û�դ�Ĺ�� */
#define Row         8  /* �פ�Ĺ�դ�Ĺ�� */
#define PieceSize   4  /* ����礭�� */
#define MaxSymmetry 8  /* ����֤����κ���� */
#define MaxSite     ((Col + 1) * Row - 1)
#define LimSite     ((Col + 1) * (Row + 1))

char board[LimSite];
char name[2][Pieces];
int symmetry[Pieces];
int shape[Pieces][MaxSymmetry][PieceSize - 1];
int rest[Pieces];

void initialize(void)
{
    int site, piece, state;

    for (site = 0; site < MaxSite; site++)
        if (site % (Col + 1) == Col) board[site] = '*';
                                else board[site] = '\0';
    for (site = MaxSite; site < LimSite - 1; site++)
        board[site] = '*';
    board[LimSite - 1] = '\0';  /* �ֿ� */
    for (piece = 0; piece < Pieces; piece++) {
        rest[piece] = 2;
        scanf(" %c%c%d", &name[1][piece],
                         &name[0][piece], &symmetry[piece]);
        for (state = 0; state < symmetry[piece]; state++)
            for (site = 0; site < PieceSize - 1; site++)
                scanf("%d", &shape[piece][state][site]);
    }
}

void found(void)  /* ���ɽ�� */
{
    static int count = 0;
    int i, j;

    printf("\n�� %d\n\n", ++count);
    for (i = 0; i < Col; i++) {
        for (j = i; j < MaxSite; j += Col + 1)
            printf("%c", board[j]);
        printf("\n");
    }
}

void try(int site)  /* �Ƶ�Ū�˻�ߤ� */
{
    static int temp;
    int piece, state, s0, s1, s2;

    for (piece = 0; piece < Pieces; piece++) {
        if (rest[piece] == 0) continue;
        rest[piece]--;
        for (state = 0; state < symmetry[piece]; state++) {
            s0 = site + shape[piece][state][0];
            if (board[s0] != '\0') continue;
            s1 = site + shape[piece][state][1];
            if (board[s1] != '\0') continue;
            s2 = site + shape[piece][state][2];
            if (board[s2] != '\0') continue;
            board[site] = board[s0] = board[s1] = board[s2]
                        = name[rest[piece]][piece];
            temp = site;
            while (board[++temp] != '\0') ;
            if (temp < MaxSite) try(temp);  else found();
            board[site] = board[s0] = board[s1] = board[s2] = '\0';
        }
        rest[piece]++;
    }
}

int main()
{
    initialize();  try(0);
    return EXIT_SUCCESS;
}
