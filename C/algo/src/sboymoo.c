/***********************************************************
    sboymoo.c -- Boyer--Mooreˡ
***********************************************************/
/* ��άBoyer-Mooreˡ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>  /* #define UCHAR_MAX 255 */
#define DEMO         /* �ǥ�󥹥ȥ졼����� */

int position(unsigned char text[], unsigned char pattern[])
{
    int i, j, k, len;
    static int skip[UCHAR_MAX + 1];
    unsigned char c, tail;

    len = strlen((char *)pattern);  /* ʸ�����Ĺ�� */
    if (len == 0) return -1;        /* ���顼: Ĺ��0 */
    tail = pattern[len - 1];        /* �Ǹ��ʸ�� */
    if (len == 1) {                 /* Ĺ��1�ʤ��ñ! */
        for (i = 0; text[i] != '\0'; i++)
            if (text[i] == tail) return i;
    } else {                        /* Ĺ��2�ʾ�ʤ�ɽ���äơ� */
        for (i = 0; i <= UCHAR_MAX; i++) skip[i] = len;
        for (i = 0; i < len - 1; i++)
            skip[pattern[i]] = len - 1 - i;
        /* i = len - 1; */          /* ���褤��ȹ� */
        while ((c = text[i]) != '\0') {
#ifdef DEMO                         /* �ǥ�󥹥ȥ졼������� */
            printf("��: %s\n", text);
            printf("��: %*s\n", i + 1, pattern);
#endif
            if (c == tail) {
                j = len - 1;  k = i;
                while (pattern[--j] == text[--k])
                    if (j == 0) return k;  /* ���Ĥ��ä� */
            }
            i += skip[c];
        }
    }
    return -1;  /* ���Ĥ���ʤ��ä� */
}

int mygets(int n, unsigned char s[])  /* n ʸ���ޤ� s[] ���ɤ߹��� */
{
    int i, c;

    i = 0;
    while ((c = getchar()) != EOF && c != '\n')
        if (i < n) s[i++] = (unsigned char)c;
    if (i != 0) s[i] = '\0';
    return i;
}

int main()
{
    int n, m, p;
    static unsigned char
        text[256] = "supercalifragilisticexpialidocious",
        pattern[128];

    for ( ; ; ) {
        printf("�ƥ�����ʸ���� (�꥿����: %s)\n  ? ", text);
        if ((n = mygets(127, text)) == 0) n = strlen((char *)text);
        printf("�ȹ�ʸ���� (�꥿����: ��λ)\n  ? ");
        if ((m = mygets(127, pattern)) == 0) break;
        memset(text + n, 0, m);
        p = position(text, pattern);
        if (p >= 0) printf("���� = %d\n\n", p);
        else        printf("���Ĥ���ޤ���.\n\n");
    }
    return EXIT_SUCCESS;
}
