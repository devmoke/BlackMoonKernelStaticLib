#include "stdafx.h"
#include "limits.h"
#define XCHG(x, y) {x = x^y; y = x^y; x = x^y;}

//�������� - ȡ�����
/*
    ���ø�ʽ�� �������͡� ȡ����� ���������� ��ȡ���������Сֵ�ݣ��������� ��ȡ����������ֵ�ݣ� - ϵͳ����֧�ֿ�->��������
    Ӣ�����ƣ�rnd
    ����һ��ָ����Χ�ڵ������ֵ����ʹ�ñ�����ȡһϵ�е������֮ǰ��Ӧ����ʹ�á�����������ӡ�����Ϊ�������������ʼ��һ������ֵ��������Ϊ�������
    ����<1>������Ϊ����ȡ���������Сֵ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����������ڻ�����㡣�����������ʡ�ԣ�Ĭ��Ϊ 0 ��
    ����<2>������Ϊ����ȡ����������ֵ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����������ڻ�����㡣�����������ʡ�ԣ�Ĭ��Ϊ���ޡ�
*/
LIBAPI(int, krnln_rnd)
{
	PMDATA_INF pArg = &ArgInf;

	register int nMin;
	register int nMax;

	// check for min value
	if (pArg[0].m_dtDataType != _SDT_NULL)
		nMin = pArg[0].m_int < 0 ? 0 : pArg[0].m_int;
	else nMin = 0;

	// check for max value
	if (pArg[1].m_dtDataType != _SDT_NULL)
		nMax = pArg[1].m_int < 0 ? 0 : pArg[1].m_int;
	else nMax = INT_MAX;

	// if min bigger than max
	// xchg them
	if(nMin > nMax)
		XCHG(nMin, nMax);
	
	return nMin + (rand() % (nMax - nMin + 1));

}
