#include "stdafx.h"
#include <math.h>
//ʱ����� - ȡ���
/*
    ���ø�ʽ�� �������͡� ȡ��� ������ʱ���� ʱ�䣩 - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�year
    ����һ��ֵΪ 100 �� 9999 ֮�����������ʾָ��ʱ���е���ݡ�������Ϊ�������
    ����<1>������Ϊ��ʱ�䡱������Ϊ������ʱ���ͣ�date������
*/
LIBAPI(int, krnln_year)
{
	DATE objDate;
	INT nYear, nMonth, nDay;
	DATE dt = modf(ArgInf.m_date,&objDate);
	GetDatePart(objDate,nYear, nMonth, nDay);
	return nYear;
}
