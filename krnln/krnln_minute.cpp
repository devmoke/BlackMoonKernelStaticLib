#include "stdafx.h"
#include <math.h>
//ʱ����� - ȡ����
/*
    ���ø�ʽ�� �������͡� ȡ���� ������ʱ���� ʱ�䣩 - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�minute
    ����һ��ֵΪ 0 �� 59 ֮�����������ʾһСʱ�е�ĳһ���ӡ�������Ϊ�������
    ����<1>������Ϊ��ʱ�䡱������Ϊ������ʱ���ͣ�date������
*/
LIBAPI(int, krnln_minute)
{
	DATE objDate;
	DATE dt = modf(ArgInf.m_date,&objDate);
	INT nHour, nMinute, nSecond;
	GetTimePart(dt,nHour, nMinute, nSecond);
	return nMinute;
}
