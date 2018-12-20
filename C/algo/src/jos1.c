/***********************************************************
    jos1.c -- Josephus (�襻�ե�) ������
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int j, k, n, p;

    printf("�Ϳ�? ");  scanf("%d", &n);
    printf("���ͤ���? ");  scanf("%d", &p);
    k = 1;
    for (j = 2; j <= n; j++) {
        k = (k + p) % j;
        if (k == 0) k = j;
    }
    printf("%d �֤οͤ��Ĥ�ޤ�\n", k);
    return EXIT_SUCCESS;
}
