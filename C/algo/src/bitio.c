/***********************************************************
    bitio.c -- Huffman (�ϥեޥ�) ˡ
***********************************************************/

/* Huffmanˡ�ʤɤǻȤ��ӥå������ϥ롼���� */

#include <stdio.h>
#include <stdlib.h>

FILE *infile, *outfile;      /* ���ϥե�����, ���ϥե����� */
unsigned long outcount = 0;  /* ���ϥХ��ȿ������� */
static int getcount = 0, putcount = 8;  /* �ӥå������ϥ����� */
static unsigned bitbuf = 0;  /* �ӥå������ϥХåե� */
#define rightbits(n, x) ((x) & ((1U << (n)) - 1U))  /* x�α�n�ӥå� */

void error(char *message)  /* ��å�������ɽ������λ */
{
    fprintf(stderr, "\n%s\n", message);
    exit(EXIT_FAILURE);
}

unsigned getbit(void)  /* 1�ӥå��ɤ� */
{
    if (--getcount >= 0) return (bitbuf >> getcount) & 1U;
    getcount = 7;  bitbuf = getc(infile);
    return (bitbuf >> 7) & 1U;
}

unsigned getbits(int n)  /* n�ӥå��ɤ� */
{
    unsigned x;

    x = 0;
    while (n > getcount) {
        n -= getcount;
        x |= rightbits(getcount, bitbuf) << n;
        bitbuf = getc(infile);  getcount = 8;
    }
    getcount -= n;
    return x | rightbits(n, bitbuf >> getcount);
}

void putbit(unsigned bit)  /* 1�ӥåȽ񤭽Ф� */
{
    putcount--;
    if (bit != 0) bitbuf |= (1 << putcount);
    if (putcount == 0) {
        if (putc(bitbuf, outfile) == EOF) error("�񤱤ޤ���");
        bitbuf = 0;  putcount = 8;  outcount++;
    }
}

void putbits(int n, unsigned x)  /* n�ӥåȽ񤭽Ф� */
{
    while (n >= putcount) {
        n -= putcount;
        bitbuf |= rightbits(putcount, x >> n);
        if (putc(bitbuf, outfile) == EOF) error("�񤱤ޤ���");
        bitbuf = 0U;  putcount = 8;  outcount++;
    }
    putcount -= n;
    bitbuf |= rightbits(n, x) << putcount;
}
