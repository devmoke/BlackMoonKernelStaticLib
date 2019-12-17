#include "stdafx.h"

//ʱ����� - ָ��ʱ��
/*
    ���ø�ʽ�� ������ʱ���͡� ָ��ʱ�� �������� �꣬�������� �£ݣ��������� �գݣ��������� Сʱ�ݣ��������� ���ӣݣ��������� ��ݣ� - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�GetSpecTime
    ���ذ���ָ���ꡢ�¡��ա�Сʱ���֡����ʱ�䡣���ָ������Чʱ�䣬���Զ�ʹ�����������Чʱ����档������Ϊ�������
    ����<1>������Ϊ���ꡱ������Ϊ�������ͣ�int������
    ����<2>������Ϊ���¡�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������������ʡ�ԣ�Ĭ��Ϊ 1 �¡�
    ����<3>������Ϊ���ա�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������������ʡ�ԣ�Ĭ��Ϊ 1 �ա�
    ����<4>������Ϊ��Сʱ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������������ʡ�ԣ�Ĭ��Ϊ 0 ʱ��
    ����<5>������Ϊ�����ӡ�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������������ʡ�ԣ�Ĭ��Ϊ 0 ���ӡ�
    ����<6>������Ϊ���롱������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������������ʡ�ԣ�Ĭ��Ϊ 0 �롣
*/
LIBAPI(void, krnln_GetSpecTime) // ֱ���޸���eax��eax,���Բ���Ҫָ������ֵ����
{
	PMDATA_INF pArgInf = &ArgInf;	
	INT nYear, nMonth, nDay;
	INT nHour, nMinute, nSecond;
	nYear = pArgInf[0].m_int;
	if(nYear < 100) nYear =100;

	if(pArgInf[1].m_dtDataType ==_SDT_NULL)
		nMonth = 1;
	else
	{
		nMonth = pArgInf[1].m_int;
		if(nMonth < 1)
			nMonth =1;
		else if (nMonth > 12)
			nMonth =12;
	}

	if(pArgInf[2].m_dtDataType ==_SDT_NULL)
		nDay = 1;
	else
	{
		nDay = pArgInf[2].m_int;
		if(nDay < 1)
			nDay = 1;
		else
		{
			INT nMaxDay = GetDaysOfSpecMonth(nYear,nMonth);
			if(nDay > nMaxDay)
				nDay = nMaxDay;
		}
	}

	nHour = pArgInf[3].m_int;
	if(nHour < 0)
		nHour = 0;
	else if (nHour > 23)
		nHour = 23;

	nMinute = pArgInf[4].m_int;
	if(nMinute < 0)
		nMinute = 0;
	else if (nMinute > 59)
		nMinute = 59;

	nSecond = pArgInf[5].m_int;
	if(nSecond < 0)
		nSecond = 0;
	else if (nSecond > 59)
		nSecond = 59;

	ArgInf.m_double = GetSpecDateTime(nYear, nMonth, nDay, nHour, nMinute, nSecond);
	__asm{
		mov eax, ArgInf.m_unit.m_dwFormID;
		mov edx, ArgInf.m_unit.m_dwUnitID;
	}
}
