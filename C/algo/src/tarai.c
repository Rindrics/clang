/***********************************************************
    tarai.c -- ���餤�ޤ路�ؿ�
***********************************************************/

int tarai(int x, int y, int z)
{
    if (x <= y) return y;
    return tarai(tarai(x - 1, y, z),
                 tarai(y - 1, z, x),
                 tarai(z - 1, x, y));
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x, y, z;

    printf("x = ");  scanf("%d", &x);
    printf("y = ");  scanf("%d", &y);
    printf("z = ");  scanf("%d", &z);
    printf("tarai(x, y, z) = %d\n", tarai(x, y, z));
    return EXIT_SUCCESS;
}
