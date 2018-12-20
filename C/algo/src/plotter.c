/***********************************************************
    plotter.c -- ����ե��å���
***********************************************************/
/* �ץ�å��Υ��ߥ�졼����� */

#include "gr98.c"  /* �ޤ��� "grega.c".  �顼����ǥ�ǥ���ѥ��� */
#include "window.c"
static double xpen = 0, ypen = 0;  /* �ڥ�θ��߰��� */

void move(double x, double y)  /* �ڥ󥢥åפǰ�ư */
{
    xpen = x;  ypen = y;
}

void move_rel(double dx, double dy)  /* Ʊ�� (���к�ɸ) */
{
    xpen += dx;  ypen += dy;
}

void draw(double x, double y)  /* �ڥ������ǰ�ư */
{
    gr_wline(xpen, ypen, x, y, WHITE);
    xpen = x;  ypen = y;
}

void draw_rel(double dx, double dy)  /* Ʊ�� (���к�ɸ) */
{
    gr_wline(xpen, ypen, xpen + dx, ypen + dy, WHITE);
    xpen += dx;  ypen += dy;
}
