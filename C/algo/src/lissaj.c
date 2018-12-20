/***********************************************************
    lissaj.c -- Lissajous (�ꥵ���塼) �޷�
***********************************************************/
#include "plotter.c"  /* �顼����ǥ�ǥ���ѥ��� */
#include <math.h>  /* sin, cos */
#define PI 3.141592653589793

int main()
{
    int i;
    double t;

    gr_on();
    gr_window(-1, -1, 1, 1, 1, 0);  /* ��ɸ���� */
    move(cos(0), sin(0));  /* ����ڥ���� */
    for (i = 1; i <= 360; i++) {
        t = (PI / 180) * i;
        draw(cos(3 * t), sin(5 * t));  /* �ڥ��ư */
    }
    hitanykey();
    return EXIT_SUCCESS;
}
