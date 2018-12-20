/***********************************************************
    mccarthy.c -- McCarthy (�ޥå�������) �ؿ�
***********************************************************/
#define N 100

int McCarthy(int x)
{
    if (x > N) return x - 10;
    /* else */ return McCarthy(McCarthy(x + 11));
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;

    for ( ; ; ) {
        printf("0 �ʾ� %d �ʲ������� x: ", N);
        scanf("%d", &x);
        if (x < 0 || x > N) break;
        printf("McCarthy(x) = %d\n", McCarthy(x));
    }
    return EXIT_SUCCESS;
}
