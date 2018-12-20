/***********************************************************
    arith.c -- ���Ѱ���
***********************************************************/
#include "bitio.c"  /* \see\ Huffmanˡ */
#include <limits.h>
#ifdef max
    #undef max
#endif
#define max(x, y) ((x) > (y) ? (x) : (y))  /* 2���κ����� */
#define N  256      /* ʸ���μ��� (ʸ��������{\tt = 0..N-1}) */
#define USHRT_BIT (CHAR_BIT * sizeof(unsigned short))
                    /* {\tt unsigned short} �Υӥåȿ� */
#define Q1 (1U << (USHRT_BIT - 2))
#define Q2 (2U * Q1)
#define Q3 (3U * Q1)

unsigned cum[N + 1];  /* �����ٿ� */
int ns;  /* ���� {\tt output()} �ǽ��Ϥ�������Υ����� */

static void output(int bit)  /* {\tt bit} ��³���Ƥ�������� {\tt ns} �Ľ��� */
{
    putbit(bit);  /* 1�ӥåȽ񤭽Ф� */
    while (ns > 0) {  putbit(! bit);  ns--;  }  /* ���������񤭽Ф� */
}

void encode(void)  /* ���� */
{
    int c;
    unsigned long range, maxcount, incount, cr, d;
    unsigned short low, high;
    static unsigned long count[N];

    for (c = 0; c < N; c++) count[c] = 0;  /* ���٤ν���� */
    while ((c = getc(infile)) != EOF) count[c]++;  /* ��ʸ�������� */
    incount = 0;  maxcount = 0;  /* ��ʸ���礭��, ���٤κ����� */
    for (c = 0; c < N; c++) {
        incount += count[c];
        if (count[c] > maxcount) maxcount = count[c];
    }
    if (incount == 0) return;  /* 0�Х��ȤΥե����� */
    /* ���ٹ�פ� {\tt Q1} ̤��, �����٤�1�Х��Ȥ˼��ޤ�褦���ʲ� */
    d = max((maxcount + N - 2) / (N - 1),
            (incount + Q1 - 257) / (Q1 - 256));
    if (d != 1)
        for (c = 0; c < N; c++)
            count[c] = (count[c] + d - 1) / d;
    cum[0] = 0;
    for (c = 0; c < N; c++) {
        fputc((int)count[c], outfile);  /* ����ɽ�ν��� */
        cum[c + 1] = cum[c] + (unsigned)count[c];  /* �������� */
    }
    outcount = N;
    rewind(infile);  incount = 0;  /* �����ᤷ�ƺ����� */
    low = 0;  high = USHRT_MAX;  ns = 0;
    while ((c = getc(infile)) != EOF) {  /* ��ʸ������沽 */
        range = (unsigned long)(high - low) + 1;
        high = (unsigned short)
               (low + (range * cum[c + 1]) / cum[N] - 1);
        low  = (unsigned short)
               (low + (range * cum[c    ]) / cum[N]);
        for ( ; ; ) {
            if      (high < Q2) output(0);
            else if (low >= Q2) output(1);
            else if (low >= Q1 && high < Q3) {
                ns++;  low -= Q1;  high -= Q1;
            } else break;
            low <<= 1;  high = (high << 1) + 1;
        }
        if ((++incount & 1023) == 0) printf("%12lu\r", incount);
    }
    ns += 8;  /* �Ǹ��7�ӥåȤϥХåե��ե�å���Τ��� */
    if (low < Q1) output(0);  else output(1);  /* 01�ޤ���10 */
    printf("In : %lu bytes\n", incount);  /* ��ʸ���礭�� */
    printf("Out: %lu bytes (table: %d)\n", outcount, N);
    cr = (1000 * outcount + incount / 2) / incount;  /* ������ */
    printf("Out/In: %lu.%03lu\n", cr / 1000, cr % 1000);
}

int binarysearch(unsigned x)  /* $\mbox{\tt cum[i]} \le x < \mbox{\tt cum[i+1]}$ �Ȥʤ� {\tt i} ����ʬõ���ǵ��� */
{
    int i, j, k;

    i = 1;  j = N;
    while (i < j) {
        k = (i + j) / 2;
        if (cum[k] <= x) i = k + 1;  else j = k;
    }
    return i - 1;
}

void decode(unsigned long size)  /* ���� */
{
    int c;
    unsigned char count[N];
    unsigned short low, high, value;
    unsigned long i, range;

    if (size == 0) return;  /* 0�Х��ȤΥե����� */
    cum[0] = 0;
    for (c = 0; c < N; c++) {
        count[c] = fgetc(infile);  /* ����ʬ�ۤ��ɤ� */
        cum[c + 1] = cum[c] + count[c];  /* �������٤���� */
    }
    value = 0;
    for (c = 0; c < USHRT_BIT; c++)
        value = 2 * value + getbit();  /* �Хåե��������� */
    low = 0;  high = USHRT_MAX;
    for (i = 0; i < size; i++) {  /* ��ʸ������������ */
        range = (unsigned long)(high - low) + 1;
        c = binarysearch((unsigned)((((unsigned long)
            (value - low) + 1) * cum[N] - 1) / range));
        high = (unsigned short)
               (low + (range * cum[c + 1]) / cum[N] - 1);
        low  = (unsigned short)
               (low + (range * cum[c    ]) / cum[N]);
        for ( ; ; ) {
            if      (high < Q2) { /* ���⤷�ʤ� */ }
            else if (low >= Q2) { /* ���⤷�ʤ� */ }
            else if (low >= Q1 && high < Q3) {
                value -= Q1;  low -= Q1;  high -= Q1;
            } else break;
            low <<= 1;  high = (high << 1) + 1;
            value = (value << 1) + getbit();  /* 1�ӥå��ɤ� */
        }
        putc(c, outfile);  /* ��������ʸ����񤭽Ф� */
        if ((i & 1023) == 0) printf("%12lu\r", i);
    }
    printf("%12lu\n", size);  /* ��ʸ�ΥХ��ȿ� */
}

int main(int argc, char *argv[])
{
    int c;
    unsigned long size;  /* ���ΥХ��ȿ� */

    if (argc != 4 || ((c = *argv[1]) != 'E' && c != 'e'
                                && c != 'D' && c != 'd'))
        error("����ˡ����ʸ�򻲾Ȥ��Ƥ�������");
    if ((infile  = fopen(argv[2], "rb")) == NULL)
        error("���ϥե����뤬�����ޤ���");
    if ((outfile = fopen(argv[3], "wb")) == NULL)
        error("���ϥե����뤬�����ޤ���");
    if (c == 'E' || c == 'e') {
        fseek(infile, 0L, SEEK_END);  /* infile ��������õ�� */
        size = ftell(infile);         /* infile �ΥХ��ȿ� */
        fwrite(&size, sizeof size, 1, outfile);
        rewind(infile);
        encode();       /* ���� */
    } else {
        fread(&size, sizeof size, 1, infile);  /* ���ΥХ��ȿ� */
        decode(size);   /* ���� */
    }
    fclose(infile);  fclose(outfile);
    return EXIT_SUCCESS;
}
