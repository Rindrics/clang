/***********************************************************
    tree.c -- 2ʬõ����
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char keytype[21];

typedef struct node {
    struct node *left, *right;
    keytype key;
} *nodeptr;

struct node nil;
nodeptr root = &nil;

nodeptr insert(keytype key)  /* ���� (��Ͽ) */
{
    int cmp;
    nodeptr *p, q;

    strcpy(nil.key, key);  /* �ֿ� */
    p = &root;
    while ((cmp = strcmp(key, (*p)->key)) != 0)
        if (cmp < 0) p = &((*p)->left );
        else         p = &((*p)->right);
    if (*p != &nil) return NULL;  /* ���Ǥ���Ͽ����Ƥ��� */
    if ((q = malloc(sizeof *q)) == NULL) {
        printf("������­.\n");  exit(EXIT_FAILURE);
    }
    strcpy(q->key, key);
    q->left = &nil;  q->right = *p;  *p = q;
    return q;  /* ��Ͽ���� */
}

int delete(keytype key)  /* ����Ǥ���� 0, ���Ԥʤ� 1 ���֤� */
{
    int cmp;
    nodeptr *p, *q, r, s;

    strcpy(nil.key, key);  /* �ֿ� */
    p = &root;
    while ((cmp = strcmp(key, (*p)->key)) != 0)
        if (cmp < 0) p = &((*p)->left);
        else         p = &((*p)->right);
    if (*p == &nil) return 1;  /* ���Ĥ��餺 */
    r = *p;
    if      (r->right == &nil) *p = r->left;
    else if (r->left  == &nil) *p = r->right;
    else {
        q = &(r->left);
        while ((*q)->right != &nil) q = &((*q)->right);
        s = *q;  *q = s->left;
        s->left = r->left;  s->right = r->right;
        *p = s;
    }
    free(r);
    return 0;  /* ������� */
}

nodeptr search(keytype key)  /* ���� (̤��Ͽ�ʤ�NULL���֤�) */
{
    int cmp;
    nodeptr p;

    strcpy(nil.key, key);  /* �ֿ� */
    p = root;
    while ((cmp = strcmp(key, p->key)) != 0)
        if (cmp < 0) p = p->left;
        else         p = p->right;
    if (p != &nil) return p;     /* ���Ĥ��ä� */
    else           return NULL;  /* ���Ĥ���ʤ� */
}

void printtree(nodeptr p)
{
    static int depth = 0;

    if (p->left != &nil) {
        depth++;  printtree(p->left);  depth--;
    }
    printf("%*c%s\n", 5 * depth, ' ', p->key);
    if (p->right != &nil) {
        depth++;  printtree(p->right);  depth--;
    }
}

int main()
{
    char buf[22];

    printf("̿�� Iabc:  abc������\n"
           "     Dabc:  abc����\n"
           "     Sabc:  abc�򸡺�\n");
    for ( ; ; ) {
        printf("̿��? ");
        if (scanf("%21s%*[^\n]", buf) != 1) break;
        switch (buf[0]) {
        case 'I':  case 'i':
            if (insert(&buf[1])) printf("��Ͽ���ޤ���.\n");
            else                 printf("��Ͽ���ߤǤ�.\n");
            break;
        case 'D':  case 'd':
            if (delete(&buf[1])) printf("��Ͽ����Ƥ��ޤ���.\n");
            else                 printf("������ޤ���.\n");
            break;
        case 'S':  case 's':
            if (search(&buf[1])) printf("��Ͽ����Ƥ��ޤ�.\n");
            else                 printf("��Ͽ����Ƥ��ޤ���\n");
            break;
        default:
            printf("�Ȥ���Τ� I, D, S �Ǥ�.\n");
            break;
        }
        if (root != &nil) {
            printf("\n");  printtree(root);  printf("\n");
        }
    }
    return EXIT_SUCCESS;
}
