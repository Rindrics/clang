/***********************************************************
    dragon.c -- �ɥ饴�󥫡���
***********************************************************/
#include "plotter.c"  /* �顼����ǥ�ǥ���ѥ��� */

void dragon(int i, double dx, double dy, int sign)
{
    if (i == 0) draw_rel(dx, dy);
    else {
        dragon(i-1, (dx-sign*dy)/2, (dy+sign*dx)/2,  1);
        dragon(i-1, (dx+sign*dy)/2, (dy-sign*dx)/2, -1);
    }
}

int main()
{
    int order;

    printf("�̿� = ");  scanf("%d", &order);
    gr_on();  gr_window(0, 0, 4, 3, 1, GREEN);
    move(1, 1);  dragon(order, 2, 0, 1);
    hitanykey();
    return EXIT_SUCCESS;
}
