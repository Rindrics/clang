/***********************************************************
    solst.c -- �����ȿ���õ��
***********************************************************/
/* ��Ƭ��ưˡ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYSIZE     15  /* ̾������礭�� */
#define INFOSIZE   127  /* ��������礭�� */
typedef char keytype[KEYSIZE + 1], infotype[INFOSIZE + 1];
typedef struct item {
    struct item *next;
    keytype key;
    infotype info;
} *pointer;

static struct item head = { &head, "", "" };  /* �ꥹ�Ȥ�Ƭ */

void insert(keytype key, infotype info)
{
    pointer p;

    if ((p = malloc(sizeof *p)) == NULL) {
        printf("������­.\n");  exit(EXIT_FAILURE);
    }
    strcpy(p->key, key);  strcpy(p->info, info);
    p->next = head.next;  head.next = p;
}

pointer search(keytype x)
{
    pointer p, q;

    strcpy(head.key, x);  p = &head;  /* �ֿ� */
    do {
        q = p;  p = p->next;
    } while (strcmp(p->key, x) != 0);
    if (p == &head) return NULL;
    q->next = p->next;  p->next = head.next;  head.next = p;
    return p;
}

#define ReadString(len, x) (scanf("%" #len "s%*[^\n]", x) == 1)

int main()
{
    keytype key;
    infotype info;
    pointer p;

    for ( ; ; ) {
        printf("̾��? ");
        if (! ReadString(KEYSIZE, key)) break;
        if ((p = search(key)) != NULL)
            printf("����: %s\n", p->info);
        else {
            printf("����? ");
            if (ReadString(INFOSIZE, info)) insert(key, info);
        }
    }
    return EXIT_SUCCESS;
}
