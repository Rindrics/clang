/***********************************************************
    tbintree.c -- �Ҥ��դ�2ʬ��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char keytype[21];  /* õ���Υ����η� */
typedef struct node {      /* struct node ���ڤΥΡ��� */
    struct node *left, *right;  /* �����λҤؤΥݥ��� */
    unsigned int count;    /* ���Ȳ�������� */
    keytype key;           /* õ���Υ���(��Ͽʸ����) */
    char flags;            /* ��ʸ���� */
} *nodeptr;  /* {\tt nodeptr} �ϥΡ��ɤؤΥݥ��� */

#define LBIT 1  /* ��� {\tt flags} ���������� */
#define RBIT 2

struct node root = {&root, &root, 0, "", 0};  /* �ڤκ� */

nodeptr newnode(keytype key)  /* �������Ρ��ɤ����� */
{
    nodeptr p;

    if ((p = malloc(sizeof *p)) == NULL) {
        printf("������­.\n");  exit(EXIT_FAILURE);
    }
    strcpy(p->key, key);  /* �����򥳥ԡ����� */
    p->count = 1;         /* ���Ȳ����1�ˤ��� */
    return p;
}

void insertright(nodeptr p, keytype key)  /* �Ρ��� p �α������� */
{
    nodeptr q;

    q = newnode(key);     /* �������Ρ��ɤ����� */
    q->right = p->right;  /* ���λҤϿƤα��λҤ�����Ѥ� */
    q->left = p;          /* ���λҤϤ��ĤϿƤ�ؤ��Ҥ� */
    q->flags = p->flags & RBIT;  /* ���ե饰�ϿƤα��ե饰������Ѥ� */
    p->flags |= RBIT;     /* {\tt q} �ϤҤ�Ǥʤ��ΤǿƤα��ե饰��Ω�Ƥ� */
    p->right = q;         /* {\tt q} ��� {\tt p} �α��λҤˤ��� */
}

void insertleft(nodeptr p, keytype key)  /* �Ρ��� p �κ������� */
{                                        /* �����Ͼ��Ʊ�ͤʤΤǾʤ� */
    nodeptr q;

    q = newnode(key);
    q->left = p->left;  q->right = p;
    q->flags = p->flags & LBIT;
    p->flags |= LBIT;  p->left = q;
}

void insert(keytype key)  /* ����(��Ͽ) */
{
    int cmp;    /* ��ӷ�� */
    nodeptr p;

    p = &root;  cmp = 1;  /* �ǽ�λҤϿƤα��� */
    do {
        if (cmp < 0) {    /* ��������к�����Ͽ */
            if (p->flags & LBIT) p = p->left;
            else {  insertleft(p, key);  return;  }
        } else {          /* �礭����б�����Ͽ */
            if (p->flags & RBIT) p = p->right;
            else {  insertright(p, key);  return;  }
        }
    } while ((cmp = strcmp(key, p->key)) != 0);
    p->count++;           /* ��������л��Ȳ������������ */
}

nodeptr successor(nodeptr p)  /* ����� {\tt p} ��ľ��ΥΡ��� */
{  /* ${\tt right} \leftrightarrow {\tt left}$, ${\tt RBIT} \leftrightarrow {\tt LBIT}$ �Ȥ����ľ���ΥΡ��ɤˤʤ� */
    nodeptr q;

    q = p->right;
    if (p->flags & RBIT)
        while (q->flags & LBIT) q = q->left;
    return q;
}

void printinorder(void)  /* ���������������� */
{
    nodeptr p;

    p = &root;
    while ((p = successor(p)) != &root)
        printf("%-20s %5d\n", p->key, p->count);
}

int main()
{
    char word[21];

    while (scanf("%20s%*[^ \n\t]", word) == 1)
        insert(word);  /* ɸ�����Ϥ���ñ����ɤ���Ͽ */
    printinorder();    /* ��ñ��Ƚи�����򾺽�˽��� */
    return EXIT_SUCCESS;
}
