#include "stdafx.h"
#include <math.h>
//ʱ����� - ������ʱ��
/*
    ���ø�ʽ�� ���߼��͡� ������ʱ�� ������ʱ���� �����õ�ʱ�䣩 - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�SetSysTime
    ���õ�ǰϵͳ���ڼ�ʱ�䡣�ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ�������õ�ʱ�䡱������Ϊ������ʱ���ͣ�date������
*/
LIBAPI(BOOL, krnln_SetSysTime)
{
	SYSTEMTIME now;
	memset(&now,0,sizeof(SYSTEMTIME));
	DATE objDate;
	INT nYear, nMonth, nDay;
	INT nHour, nMinute, nSecond;
	DATE dt = modf(ArgInf.m_date,&objDate);
	GetDatePart(objDate,nYear, nMonth, nDay);
	GetTimePart(dt,nHour, nMinute, nSecond);
	now.wYear = nYear;
	now.wMonth = nMonth;
	now.wDay = nDay;
	now.wHour = nHour;
	now.wMinute = nMinute;
	now.wSecond = nSecond;
	return SetLocalTime(&now);
}
