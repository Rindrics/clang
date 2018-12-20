/***********************************************************
    water.c -- ���Ϥ�������
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int gcd(int x, int y)  /* �������� */
{
    if (x == 0) return y;  else return gcd(y % x, x);
}

int main()
{
    int a, b, v, x, y;

    printf("�ƴ��������? ");  scanf("%d", &a);
    printf("�ƴ�¤�����? ");  scanf("%d", &b);
    printf("�Ϥ��ꤿ������? ");  scanf("%d", &v);
    if (v > a && v > b || v % gcd(a, b) != 0) {
        printf("�Ϥ���ޤ���\n");  return EXIT_FAILURE;
    }
    x = y = 0;
    do {
        if (x == 0) {
            printf("���˿���������ޤ�\n");  x = a;
        } else if (y == b) {
            printf("�¤���ˤ��ޤ�\n");  y = 0;
        } else if (x < b - y) {
            printf("���ο�򤹤٤ƣ¤˰ܤ��ޤ�\n");
            y += x;  x = 0;
        } else {
            printf("���ο��¤����äѤ��ˤʤ�ޤ�"
                "�¤˰ܤ��ޤ�\n");  x -= b - y;  y = b;
        }
    } while (x != v && y != v);
    if      (x == v) printf("���ˤϤ���ޤ���\n");
    else if (y == v) printf("�¤ˤϤ���ޤ���\n");
    return EXIT_SUCCESS;
}
