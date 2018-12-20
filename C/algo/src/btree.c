/***********************************************************
    btree.c -- B��
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define M  2  /* 1�ڡ����Υǡ������ξ�¤�Ⱦʬ */

typedef int keytype;                 /* õ���Υ����η� */
typedef enum {FALSE, TRUE} boolean;  /* ${\tt FALSE} = 0$, ${\tt TRUE} = 1$ */

typedef struct page {                /* �ڡ�������� */
    int n;                           /* �ǡ����� */
    keytype key[2 * M];              /* ���� */
    struct page *branch[2 * M + 1];  /* ¾�ڡ����ؤΥݥ��� */
} *pageptr;        /* {\tt pageptr} �ϥڡ����ؤΥݥ��󥿤η� */

pageptr root = NULL;                 /* B�ڤκ� */
keytype key;                         /* ���� */
boolean done, deleted, undersize;    /* ���������ѿ� */
pageptr newp;       /* {\tt insert()} �����������������ڡ��� */
char *message;                       /* �ؿ����֤���å����� */

pageptr newpage(void)  /* �������ڡ��������� */
{
    pageptr p;

    if ((p = malloc(sizeof *p)) == NULL) {
        printf("������­.\n");  exit(EXIT_FAILURE);
    }
    return p;
}

void search(void)  /* ���� {\tt key} ��B�ڤ���õ�� */
{
    pageptr p;
    int k;

    p = root;
    while (p != NULL) {
        k = 0;
        while (k < p->n && p->key[k] < key) k++;
        if (k < p->n && p->key[k] == key) {
            message = "���Ĥ���ޤ���";  return;
        }
        p = p->branch[k];
    }
    message = "���Ĥ���ޤ���";
}

void insertitem(pageptr p, int k)  /* {\tt key} �� {\tt p->key[k]} ������ */
{
    int i;

    for (i = p->n; i > k; i--) {
        p->key[i] = p->key[i - 1];
        p->branch[i + 1] = p->branch[i];
    }
    p->key[k] = key;  p->branch[k + 1] = newp;  p->n++;
}

void split(pageptr p, int k)  /* {\tt key} �� {\tt p->key[k]} ��������, �ڡ��� {\tt p} ���� */
{
    int j, m;
    pageptr q;

    if (k <= M) m = M;  else m = M + 1;
    q = newpage();
    for (j = m + 1; j <= 2 * M; j++) {
        q->key[j - m - 1] = p->key[j - 1];
        q->branch[j - m] = p->branch[j];
    }
    q->n = 2 * M - m;  p->n = m;
    if (k <= M) insertitem(p, k);
    else        insertitem(q, k - m);
    key = p->key[p->n - 1];
    q->branch[0] = p->branch[p->n];  p->n--;
    newp = q;  /* �������ڡ����� {\tt newp} ���������� */
}

void insertsub(pageptr p)  /* {\tt p} �����ڤ�Ƶ�Ū�ˤ��ɤä����� */
{
    int k;

    if (p == NULL) {
        done = FALSE;  newp = NULL;  return;
    }
    k = 0;
    while (k < p->n && p->key[k] < key) k++;
    if (k < p->n && p->key[k] == key) {
        message = "�⤦��Ͽ����Ƥ��ޤ�";  done = TRUE;
        return;
    }
    insertsub(p->branch[k]);
    if (done) return;
    if (p->n < 2 * M) {   /* �ڡ��������ʤ���� */
        insertitem(p, k);  done = TRUE;
    } else {              /* �ڡ����������� */
        split(p, k);  done = FALSE;
    }
}

void insert(void)  /* ���� {\tt key} ��B�ڤ����� */
{
    pageptr p;

    message = "��Ͽ���ޤ���";
    insertsub(root);  if (done) return;
    p = newpage();  p->n = 1;  p->key[0] = key;
    p->branch[0] = root;  p->branch[1] = newp;  root = p;
}

void removeitem(pageptr p, int k)
    /* {\tt p->key[k]}, {\tt p->branch[k+1]} �򳰤�. */
    /* �ڡ������������ʤꤹ������ {\tt undersize} �ե饰��Ω�Ƥ�. */
{
    while (++k < p->n) {
        p->key[k - 1] = p->key[k];
        p->branch[k] = p->branch[k + 1];
    }
    undersize = --(p->n) < M;
}

void moveright(pageptr p, int k)
    /* {\tt p->branch[k - 1]} �κǱ����Ǥ� */
    /* {\tt p->key[k - 1]} ��ͳ�� {\tt p->branch[k]} ��ư���� */
{
    int j;
    pageptr left, right;

    left = p->branch[k - 1];  right = p->branch[k];
    for (j = right->n; j > 0; j--) {
        right->key[j] = right->key[j - 1];
        right->branch[j + 1] = right->branch[j];
    }
    right->branch[1] = right->branch[0];
    right->n++;
    right->key[0] = p->key[k - 1];
    p->key[k - 1] = left->key[left->n - 1];
    right->branch[0] = left->branch[left->n];
    left->n--;
}

void moveleft(pageptr p, int k)
    /* {\tt p->branch[k]} �κǺ����Ǥ� */
    /* {\tt p->key[k - 1]} ��ͳ�� {\tt p->branch[k - 1]} ��ư���� */
{
    int j;
    pageptr left, right;

    left = p->branch[k - 1];  right = p->branch[k];
    left->n++;
    left->key[left->n - 1] = p->key[k - 1];
    left->branch[left->n] = right->branch[0];
    p->key[k - 1] = right->key[0];
    right->branch[0] = right->branch[1];
    right->n--;
    for (j = 1; j <= right->n; j++) {
        right->key[j - 1] = right->key[j];
        right->branch[j] = right->branch[j + 1];
    }
}

void combine(pageptr p, int k)  /* {\tt p->branch[k - 1]}, {\tt p->branch[k]} ���礹�� */
{
    int j;
    pageptr left, right;

    right = p->branch[k];
    left = p->branch[k - 1];
    left->n++;
    left->key[left->n - 1] = p->key[k - 1];
    left->branch[left->n] = right->branch[0];
    for (j = 1; j <= right->n; j++) {
        left->n++;
        left->key[left->n - 1] = right->key[j - 1];
        left->branch[left->n] = right->branch[j];
    }
    removeitem(p, k - 1);
    free(right);
}

void restore(pageptr p, int k)  /* �������ʤꤹ�����ڡ��� {\tt p->branch[k]} �������� */
{
    undersize = FALSE;
    if (k > 0) {
        if (p->branch[k - 1]->n > M) moveright(p, k);
        else combine(p, k);
    } else {
        if (p->branch[1]->n > M) moveleft(p, 1);
        else combine(p, 1);
    }
}

void deletesub(pageptr p)  /* �ڡ��� {\tt p} ����Ƶ�Ū���ڤ򤿤ɤ��� */
{
    int k;
    pageptr q;

    if (p == NULL) return;  /* ���Ĥ���ʤ��ä� */
    k = 0;
    while (k < p->n && p->key[k] < key) k++;
    if (k < p->n && p->key[k] == key) {  /* ���Ĥ��ä� */
        deleted = TRUE;
        if ((q = p->branch[k + 1]) != NULL) {
            while (q->branch[0] != NULL) q = q->branch[0];
            p->key[k] = key = q->key[0];
            deletesub(p->branch[k + 1]);
            if (undersize) restore(p, k + 1);
        } else removeitem(p, k);
    } else {
        deletesub(p->branch[k]);
        if (undersize) restore(p, k);
    }
}

void delete(void)  /* ���� {\tt key} ��B�ڤ��鳰�� */
{
    pageptr p;

    deleted = undersize = FALSE;
    deletesub(root);  /* ������Ƶ�Ū���ڤ򤿤ɤ������� */
    if (deleted) {
        if (root->n == 0) {  /* �������ˤʤä���� */
            p = root;  root = root->branch[0];  free(p);
        }
        message = "������ޤ���";
    } else message = "���Ĥ���ޤ���";
}

void printtree(pageptr p)  /* �ǥ��Ѥ�B�ڤ�ɽ�� */
{
    static int depth = 0;
    int k;

    if (p == NULL) {  printf(".");  return;  }
    printf("(");  depth++;
    for (k = 0; k < p->n; k++) {
        printtree(p->branch[k]);  /* �Ƶ��ƽФ� */
        printf("%d", p->key[k]);
    }
    printtree(p->branch[p->n]);  /* �Ƶ��ƽФ� */
    printf(")");  depth--;
}

#include <ctype.h>

int main()
{
    char s[2];

    for ( ; ; ) {
        printf("���� In, ���� Sn, ��� Dn (n:����) ? ");
        if (scanf("%1s%d", s, &key) != 2) break;
        switch (s[0]) {
        case 'I':  case 'i':  insert();  break;
        case 'S':  case 's':  search();  break;
        case 'D':  case 'd':  delete();  break;
        default :  message = "???";  break;
        }
        printf("%s\n\n", message);
        printtree(root);  printf("\n\n");
    }
    return EXIT_SUCCESS;
}
