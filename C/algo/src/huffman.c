/***********************************************************
    huffman.c -- Huffman (�ϥեޥ�) ˡ
***********************************************************/
#include "bitio.c"              /* �ӥå������� */

#define N       256             /* ʸ���μ��� */
#define CHARBITS  8             /* 1�Х��ȤΥӥåȿ� */
int heapsize, heap[2*N-1],      /* ͥ���Ԥ������ѥҡ��� */
    parent[2*N-1], left[2*N-1], right[2*N-1];  /* Huffman�� */
unsigned long int freq[2*N-1];  /* ��ʸ���νи����� */

static void downheap(int i)  /* ͥ���Ԥ���������� */
{
    int j, k;

    k = heap[i];
    while ((j = 2 * i) <= heapsize) {
        if (j < heapsize && freq[heap[j]] > freq[heap[j + 1]])
            j++;
        if (freq[k] <= freq[heap[j]]) break;
        heap[i] = heap[j];  i = j;
    }
    heap[i] = k;
}

void writetree(int i)  /* �ޤ���� */
{
    if (i < N) {  /* �� */
        putbit(0);
        putbits(CHARBITS, i);  /* ʸ�����Τ�� */
    } else {      /* �� */
        putbit(1);
        writetree(left[i]);  writetree(right[i]);  /* �����λ� */
    }
}

void encode(void)  /* ���� */
{
    int i, j, k, avail, tablesize;
    unsigned long int incount, cr;
    static char codebit[N];  /* ���� */

    for (i = 0; i < N; i++) freq[i] = 0;  /* ���٤ν���� */
    while ((i = getc(infile)) != EOF) freq[i]++;  /* ���ٿ��� */
    heap[1] = 0;  /* Ĺ��0�Υե������������ */
    heapsize = 0;
    for (i = 0; i < N; i++)
        if (freq[i] != 0) heap[++heapsize] = i;  /* ͥ���Ԥ��������Ͽ */
    for (i = heapsize / 2; i >= 1; i--) downheap(i);  /* �ҡ��׺�� */
    for (i = 0; i < 2 * N - 1; i++) parent[i] = 0;  /* ǰ�Τ��� */
    k = heap[1];  /* �ʲ��Υ롼�פ�1���¹Ԥ���ʤ����������� */
    avail = N;  /* �ʲ��Υ롼�פǥϥեޥ��ڤ��� */
    while (heapsize > 1) {  /* 2�İʾ�Ĥ꤬����� */
        i = heap[1];  /* �Ǿ������Ǥ���Ф� */
        heap[1] = heap[heapsize--];  downheap(1);  /* �ҡ��׺ƹ��� */
        j = heap[1];  /* ���˺Ǿ������Ǥ���Ф� */
        k = avail++;  /* ����������������� */
        freq[k] = freq[i] + freq[j];  /* ���٤��� */
        heap[1] = k;  downheap(1);  /* �Ԥ��������Ͽ */
        parent[i] = k;  parent[j] = -k;  /* �ڤ��� */
        left[k] = i;  right[k] = j;      /* �� */
    }
    writetree(k);  /* �ڤ���� */
    tablesize = (int) outcount;  /* ɽ���礭�� */
    incount = 0;  rewind(infile);  /* ������ */
    while ((j = getc(infile)) != EOF) {
        k = 0;
        while ((j = parent[j]) != 0)
            if (j > 0) codebit[k++] = 0;
            else {     codebit[k++] = 1;  j = -j;  }
        while (--k >= 0) putbit(codebit[k]);
        if ((++incount & 1023) == 0)
            printf("%12lu\r", incount);  /* ������� */
    }
    putbits(7, 0);  /* �Хåե��λĤ��ե�å��� */
    printf("In : %lu bytes\n", incount);  /* ������ */
    printf("Out: %lu bytes (table: %d bytes)\n",
        outcount, tablesize);
    if (incount != 0) {  /* ������������� */
        cr = (1000 * outcount + incount / 2) / incount;
        printf("Out/In: %lu.%03lu\n", cr / 1000, cr % 1000);
    }
}

int readtree(void)  /* �ڤ��ɤ� */
{
    int i;
    static int avail = N;

    if (getbit()) {  /* bit=1: �դǤʤ��� */
        if ((i = avail++) >= 2 * N - 1) error("ɽ���ְ�äƤ��ޤ�");
        left [i] = readtree();  /* ���λޤ��ɤ� */
        right[i] = readtree();  /* ���λޤ��ɤ� */
        return i;               /* ����֤� */
    } else return (int) getbits(CHARBITS);  /* ʸ�� */
}

void decode(unsigned long int size)  /* ���� */
{
    int j, root;
    unsigned long int k;

    root = readtree();  /* �ڤ��ɤ� */
    for (k = 0; k < size; k++) {  /* ��ʸ�������� */
        j = root;  /* �� */
        while (j >= N)
            if (getbit()) j = right[j];  else j = left[j];
        putc(j, outfile);
        if ((k & 1023) == 0) printf("%12lu\r", k);  /* ���ϥХ��ȿ� */
    }
    printf("%12lu\n", size);  /* ���������Х��ȿ� */
}

int main(int argc, char *argv[])
{
    int c;
    unsigned long int size;  /* ���ΥХ��ȿ� */

    if (argc != 4 || ((c = *argv[1]) != 'E' && c != 'e'
                                && c != 'D' && c != 'd'))
        error("����ˡ����ʸ�򻲾Ȥ��Ƥ�������");
    if ((infile  = fopen(argv[2], "rb")) == NULL)
        error("���ϥե����뤬�����ޤ���");
    if ((outfile = fopen(argv[3], "wb")) == NULL)
        error("���ϥե����뤬�����ޤ���");
    if (c == 'E' || c == 'e') {
        fseek(infile, 0L, SEEK_END);  /* infile ��������õ�� */
        size = ftell(infile);     /* infile �ΥХ��ȿ� */
        fwrite(&size, sizeof size, 1, outfile);
        rewind(infile);
        encode();  /* ���� */
    } else {
        fread(&size, sizeof size, 1, infile);  /* ���ΥХ��ȿ� */
        decode(size);  /* ���� */
    }
    fclose(infile);  fclose(outfile);
    return EXIT_SUCCESS;
}
