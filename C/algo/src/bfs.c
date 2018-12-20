/***********************************************************
    bfs.c -- ����õ��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define NMAX 100                                /* ���ο��ξ�� */
char adjacent[NMAX + 1][NMAX + 1];              /* ���ܹ��� */

int n = 7;                                      /* ���ο� (��) */
int data[] = { 1, 2, 2, 3, 1, 3, 2, 4, 5, 7 };  /* �ǡ��� (��) */

void readgraph(void)  /* ��������� */
{
    int i, j, k;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) adjacent[i][j] = 0;
    for (k = 0; k < (sizeof data) / (sizeof *data); k++) {
        if (k % 2 == 0) i = data[k];
        else {
            j = data[k];
            adjacent[i][j] = adjacent[j][i] = 1;
        }
    }
    printf("���ܹ���:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
        printf("\n");
    }
}

struct queue {  /* �Ԥ����� */
    int item;
    struct queue *next;
} *head, *tail;

void initialize_queue(void)  /* �Ԥ�����ν���� */
{
    head = tail = malloc(sizeof(struct queue));
    if (head == NULL) exit(EXIT_FAILURE);
}

void addqueue(int x)  /* �Ԥ�����ؤ����� */
{
    tail->item = x;
    tail->next = malloc(sizeof(struct queue));
    if (tail->next == NULL) exit(EXIT_FAILURE);
    tail = tail->next;
}

int removequeue(void)  /* �Ԥ����󤫤�μ�Ф� */
{
    int x;
    struct queue *p;

    p = head;  head = p->next;  x = p->item;  free(p);
    return x;
}

#define START  1

int main()
{
    int i, j;
    static int distance[NMAX + 1], prev[NMAX + 1];

    initialize_queue();
    readgraph();
    for (i = 1; i <= n; i++) distance[i] = -1;
    addqueue(START);  distance[START] = 0;
    do {
        i = removequeue();
        for (j = 1; j <= n; j++)
            if (adjacent[i][j] && distance[j] < 0) {
                addqueue(j);  distance[j] = distance[i] + 1;
                prev[j] = i;
            }
    } while (head != tail);
    printf("��  ľ������  ��û��Υ\n");
    for (i = 1; i <= n; i++)
        if (distance[i] > 0)
            printf("%2d%10d%10d\n", i, prev[i], distance[i]);
    return EXIT_SUCCESS;
}
