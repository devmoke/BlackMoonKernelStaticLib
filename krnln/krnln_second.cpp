#include "stdafx.h"
#include <math.h>
//ʱ����� - ȡ��
/*
    ���ø�ʽ�� �������͡� ȡ�� ������ʱ���� ʱ�䣩 - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�second
    ����һ��ֵΪ 0 �� 59 ֮�����������ʾһ�����е�ĳһ�롣������Ϊ�������
    ����<1>������Ϊ��ʱ�䡱������Ϊ������ʱ���ͣ�date������
*/
LIBAPI(int, krnln_second)
{
	DATE objDate;
	DATE dt = modf(ArgInf.m_date,&objDate);
	INT nHour, nMinute, nSecond;
	GetTimePart(dt,nHour, nMinute, nSecond);
	return nSecond;
}
