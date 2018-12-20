/***********************************************************
    grj3.c -- ����ե��å���
************************************************************
    ����ե��å������ܥ롼���� (J-3100)
    �顼����ǥ�, ����ѥ��ȥ�ǥ�, �ҥ塼����ǥ�ʤ�,
    �ǡ����ѥݥ��󥿤�����32�ӥåȤΥ⡼�ɤǥ���ѥ���
    ���Ƥ�������.
***********************************************************/
#ifndef GRJ3_C
#define GRJ3_C

#include <stdio.h>   /* fputc, fputs, stderr */
#include <stdlib.h>  /* exit, atexit */
#include <string.h>  /* memset */
#include <dos.h>     /* union REGS, int86 */

#define XMAX  640U  /* ���ɥåȿ� */
#define YMAX  400U  /* �ĥɥåȿ� */
enum {BLACK, BLUE, RED, MAGENTA, GREEN, CYAN, YELLOW, WHITE};  /* �������� */

#define PLANE ((unsigned char *)0xb8000000L)

static union REGS regs;  /* 8086�쥸���� */
static unsigned int offset;  /* GVRAM �Υ��ե��å� */

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
            unsigned int color)  /* ����ɽ�� (color�ϥ��ߡ�) */
{
    static unsigned char
        count = 100,
        mask[] = { 128, 64, 32, 16,  8,  4,  2,  1 };

    if (--count == 0) {
        if (dgetc() == 0x1b) exit(EXIT_SUCCESS);  /* ESC */
        count = 100;
    }
    if (x >= XMAX || y >= YMAX) return;
    PLANE[(((x >> 3) + (y >> 2) * 80 + offset) & 0x1FFF)
        + (y & 3) * 0x2000] |= mask[x & 7];
}

void gr_off(void)  /* ����ե��å����̥��ꥢ */
{
    memset(PLANE, 0, 0x8000);
}

void gr_on(void)  /* ����ե��å����̽���� */
{
    static int first = 1;

    if (first) {
        atexit(gr_off);
        regs.x.ax = 0x8300;
        int86(0x10, &regs, &regs);
        offset = regs.x.ax;
        first = 0;
    }
    gr_off();                  /* ����ե��å����̥��ꥢ */
    fputs("\x1b[2J", stderr);  /* �ƥ����Ȳ��̥��ꥢ */
}

#endif  /* GRJ3_C */

#if 0  /* �ƥ��� */
int main()
{
    int i, j;

    gr_on();
    for (j = 0; j < 400; j++)
        for (i = 0; i < 640; i++)
            gr_dot(i, j, 1);
    hitanykey();
    return EXIT_SUCCESS;
}
#endif /* �ƥ��� */
