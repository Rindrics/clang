/***********************************************************
    jos2.c -- Josephus (�襻�ե�) ������
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int k, n, p;

    printf("�Ϳ�? ");  scanf("%d", &n);
    printf("���ͤ���? ");  scanf("%d", &p);
    k = p - 1;
    while (k < (p - 1) * n)
        k = (p * k) / (p - 1) + 1;
    printf("%d �֤οͤ��Ĥ�ޤ�\n", p * n - k);
    return EXIT_SUCCESS;
}
