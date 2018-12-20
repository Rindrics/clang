/***********************************************************
    gf2fact.c -- ͭ����
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int poly;        /* ¿�༰�η� */
poly quo, quo_low, res, res_low;  /* ��, ;�� */
#define MSB (~(~0U >> 1))         /* �Ǿ�̥ӥå� */
/*
  ¿�༰����Ϥ���롼����.
  ���Ȥ��� $x^3 + x + 1$ �� {\tt 1011} �Ƚ��Ϥ���.
*/
void write_poly(poly p, poly p_low)
{
    poly q;

    q = MSB;
    while (q >= p_low) {
        putchar((p & q) ? '1' : '0');
        q >>= 1;
    }
}
/*
  ¿�༰�γ�껻�Υ롼����.
  ¿�༰ {\tt a} ��¿�༰ {\tt b} �ǳ��, �� {\tt quo},
  ;�� {\tt res} �����.
  ̾���� {\TT \_low} �ǽ�����ѿ��Ϻǲ��̥ӥåȤΰ��֤�ɽ��.
  ����ڤ�뤫�ɤ�������ʬ����Ф褤�Τ�;�� {\tt res} �Ϻ��󤻤ˤ��ʤ�.
  ;��򺸴󤻤ˤ���ˤϤ��Υ롼�����
  �Ǹ�� \lq\lq {\TT res\_low} �� {\tt MSB} ��
  �ʤ���� {\TT res\_low} �� {\tt res} �򺸤�1�奷�եȤ���'' �Ȥ���
  ̿��������.
  ���ʤߤ�, ��ۤɤ� \verb"res ^= b;" �� \verb"res -= b;" �Ȥ����
  ���̤� (��ڤ�򤹤�) ��껻�ˤʤ�.
*/
void divide(poly a, poly a_low, poly b, poly b_low)
{
    quo = 0;  quo_low = MSB;  res = a;  res_low = a_low;
    if (res_low > b_low) return;
    for ( ; ; ) {
        if (res & MSB) {
            quo |= quo_low;  res ^= b;
        }
        if (res_low == b_low) break;
        res_low <<= 1;  res <<= 1;  quo_low >>= 1;
    }
}
/*
  ¿�༰ {\tt p} �����ʬ�򤹤�롼����.
*/
void factorize(poly p, poly p_low)
{
    poly d, d_low;

    d = MSB;  d_low = MSB >> 1; /* ¿�༰ {\tt d} �� $1x + 0$ �˽���� */
    while (d_low > p_low) {
        divide(p, p_low, d, d_low);  /* {\tt p} �� {\tt d} �ǳ�� */
        if (res == 0) {  /* ����ڤ���\ldots\ */
            write_poly(d, d_low);  printf("*");  /* ���� {\tt d} ����� */
            p = quo;  p_low = quo_low;  /* ���򤵤�˳�� */
        } else {  /* ����ڤ�ʤ���м���¿�༰ {\tt d} �� */
            d += d_low;  /* ����¿�༰ {\tt d} ���������� */
            if (d == 0) {
                d = MSB;  d_low >>= 1;
            }
        }
    }  /* {\tt d} �μ����� {\tt p} �μ����ʾ�ˤʤä���æ�� */
    write_poly(p, p_low);  /* �Ĥä�¿�༰ {\tt p} ����� */
}

int main()
{
    poly p, p_low;

    p = MSB;  p_low = MSB >> 1;    /* {\tt p} �� $1x + 0$ �˽���� */
    while (p_low != 0) {
        write_poly(p, p_low);  printf(" = ");
        factorize(p, p_low);  printf("\n");  /* {\tt p} �����ʬ�� */
        p += p_low;            /* ����¿�༰ {\tt p} ���������� */
        if (p == 0) {
            p = MSB;  p_low >>= 1;
        }
    }
    return EXIT_SUCCESS;
}
