/***********************************************************
    ishi1.c -- �м�ꥲ���� 1
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m, x, r, my_turn;

    printf("�Ǹ���Ф��ä�¦���餱�Ǥ�. �ѥ��ϤǤ��ޤ���.\n");
    printf("�Фο�? ");  scanf("%d", &n);
    printf("����˼��������Фο�? ");  scanf("%d", &m);
    if (n < 1 || m < 1) return EXIT_FAILURE;
    for (my_turn = 1; n != 0; my_turn ^= 1) {
        if (my_turn) {
            x = (n - 1) % (m + 1);  if (x == 0) x = 1;
            printf("��� %d �Ĥ��Ф���ޤ�.\n", x);
        } else do {
            printf("���ļ��ޤ���? ");
            r = scanf("%d", &x);  scanf("%*[^\n]");
        } while (r != 1 || x <= 0 || x > m || x > n);
        n -= x;  printf("�Ĥ�� %d �ĤǤ�.\n", n);
    }
    if (my_turn) printf("���ʤ����餱�Ǥ�!\n");
    else         printf("����餱�Ǥ�!\n");
    return EXIT_SUCCESS;
}
