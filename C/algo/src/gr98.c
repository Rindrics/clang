/***********************************************************
    gr98.c -- ����ե��å���
************************************************************
    ����ե��å������ܥ롼���� (PC-9801)
    �顼����ǥ�, ����ѥ��ȥ�ǥ�, �ҥ塼����ǥ�ʤ�,
    �ǡ����ѥݥ��󥿤�����32�ӥåȤΥ⡼�ɤǥ���ѥ���
    ���Ƥ�������.
***********************************************************/
#ifndef GR98_C
#define GR98_C

#include <stdio.h>   /* fputc, fputs, stderr */
#include <stdlib.h>  /* exit, atexit */
#include <string.h>  /* memset */
#include <dos.h>     /* union REGS, int86 */

#define XMAX  640U  /* ���ɥåȿ� */
#define YMAX  400U  /* �ĥɥåȿ� */
enum {BLACK, BLUE, RED, MAGENTA, GREEN, CYAN, YELLOW, WHITE};  /* �������� */

#define PLANE1 ((unsigned char *)0xa8000000L) /* �ĥץ졼�� */
#define PLANE2 ((unsigned char *)0xb0000000L) /* �֥ץ졼�� */
#define PLANE3 ((unsigned char *)0xb8000000L) /* �Хץ졼�� */

static union REGS regs;  /* 8086�쥸���� */

static int dgetc(void)  /* ctrl-C �ǻߤޤ�ʤ�1ʸ������ */
{                       /* ������������Ƥ��ʤ����0���֤� */
    regs.h.ah = 6;  regs.h.dl = 0xff;
    int86(0x21, &regs, &regs);  /* DOS call */
    return regs.h.al;
}

void hitanykey(void)  /* �����򲡤��ޤ��Ԥ� */
{
    fputc('\a', stderr);    /* beep */
    while (dgetc() != 0) ;  /* flush key buffer */
    while (dgetc() == 0) ;  /* wait for any key */
}

void gr_dot(unsigned int x, unsigned int y,
            unsigned int color)  /* ����ɽ�� */
{
    unsigned int i;
    unsigned char m1, m2;
    static unsigned char
        count = 100,
        mask1[] = { 128, 64, 32, 16,  8,  4,  2,  1 },
        mask2[] = { 127,191,223,239,247,251,253,254 };

    if (--count == 0) {
        if (dgetc() == 0x1b) exit(EXIT_SUCCESS);  /* ESC */
        count = 100;
    }
    if (x >= XMAX || y >= YMAX) return;
    i = 80 * y + (x >> 3);
    m1 = mask1[x & 7];  m2 = mask2[x & 7];
    if (color & 1) PLANE1[i] |= m1;  else PLANE1[i] &= m2;
    if (color & 2) PLANE2[i] |= m1;  else PLANE2[i] &= m2;
    if (color & 4) PLANE3[i] |= m1;  else PLANE3[i] &= m2;
}

void gr_off(void)  /* ����ե��å�����ɽ����� */
{
    regs.h.ah = 0x41;
    int86(0x18, &regs, &regs);  /* PC-9801 BIOS */
    fputs("\x1b[>5l", stderr);  /* ��������ɽ�� */
}

void gr_on(void)  /* ����ե��å����̽������ɽ������ */
{
    static int first = 1;

    if (first) {  atexit(gr_off);  first = 0;  }
    memset(PLANE1, 0, 32000);  /* ����ե��å����̥��ꥢ */
    memset(PLANE2, 0, 32000);
    memset(PLANE3, 0, 32000);
    /* ���̥��ꥢ, ����������ɽ��, �ǲ��ԥ桼������ */
    fputs("\x1b[2J\x1b[>5h\x1b[>1h", stderr);
    regs.h.ah = 0x42;  /* �����꡼��⡼������ */
    regs.h.ch = 0xc0;  /* 640��400 ���顼�⡼�� */
    int86(0x18, &regs, &regs);  /* PC-9801 BIOS */
    regs.h.ah = 0x40;  /* ����ե��å�����ɽ������ */
    int86(0x18, &regs, &regs);  /* PC-9801 BIOS */
}

#endif  /* GR98_C */

#if 0  /* �ƥ��� */
int main()
{
    int i, j, k, c;

    gr_on();  k = 0;
    for (c = BLACK; c < WHITE; c++) {
        for (i = 0; i < 40; i++)
            for (j = 0; j < 40; j++) gr_dot(k + i, k + j, c);
        k += 20;
    }
    for (c = WHITE; c >= BLACK; c--) {
        for (i = 0; i < 40; i++)
            for (j = 0; j < 40; j++) gr_dot(k + i, k + j, c);
        k += 20;
    }
    hitanykey();
    return EXIT_SUCCESS;
}
#endif /* �ƥ��� */
