/***********************************************************
    knapsack.c -- �ʥåץ��å�������
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000  /* �ʥåץ��å����礭���ξ�� */
#define MAXITEM  100  /* ���ܿ��ξ�� */
int maxsofar[MAXSIZE + 1], newitem[MAXSIZE + 1];
int size[MAXITEM], price[MAXITEM];

int main()
{
    int i, n, knapsize, s, space, newvalue, smallest;

    printf("�ʥåץ��å����礭��? ");  scanf("%d", &knapsize);
    if (knapsize <= 0 || knapsize > MAXSIZE) return EXIT_FAILURE;
    printf("���ܿ�? ");  scanf("%d", &n);
    if (n <= 0 || n > MAXITEM) return EXIT_FAILURE;
    for (i = 0; i < n; i++) {
        printf("���� %d ���礭��? ", i);  scanf("%d", &size[i]);
        printf("���� %d �β���  ? ", i);  scanf("%d", &price[i]);
    }

    smallest = knapsize + 1;
    for (i = 0; i < n; i++)
        if (size[i] < smallest) smallest = size[i];

    for (s = 0; s <= knapsize; s++) maxsofar[s] = 0;
    for (i = 0; i < n; i++) {
        for (s = size[i]; s <= knapsize; s++) {
            space = s - size[i];
            newvalue = maxsofar[space] + price[i];
            if (newvalue > maxsofar[s]) {
                maxsofar[s] = newvalue;  newitem[s] = i;
            }
        }
    }

    printf("����  ����\n");
    for (s = knapsize; s >= smallest; s -= size[newitem[s]])
        printf("%4d %5d\n", newitem[s], price[newitem[s]]);
    printf("��� %5d\n", maxsofar[knapsize]);

    return EXIT_SUCCESS;
}
