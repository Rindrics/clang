/***********************************************************
    chaos.c -- �������ȥ��ȥ饯��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i;
    double p, k;

    printf("�������: ");  scanf("%lf", &k);
    printf("�����  : ");  scanf("%lf", &p);
    for (i = 1; i <= 100; i++) {
        printf("%10.3f", p);
        if (i % 4 == 0) printf("\n");
        p += k * p * (1 - p);
    }
    return EXIT_SUCCESS;
}
