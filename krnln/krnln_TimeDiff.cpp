#include "stdafx.h"
#include <math.h>
//ʱ����� - ȡʱ����
/*
    ���ø�ʽ�� ��˫����С���͡� ȡʱ���� ������ʱ���� ʱ��1������ʱ���� ʱ��2�������� ȡ������֣� - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�TimeDiff
    ����һ����ֵ����ʾ��ʱ��1����ȥ��ʱ��2��֮��ļ����Ŀ��ע�⣺ÿ��������������Ϊ��һ�졣������Ϊ�������
    ����<1>������Ϊ��ʱ��1��������Ϊ������ʱ���ͣ�date������
    ����<2>������Ϊ��ʱ��2��������Ϊ������ʱ���ͣ�date������
    ����<3>������Ϊ��ȡ������֡�������Ϊ�������ͣ�int����������ֵָ��ȡʱ�����ĵ�λ������Ϊ���³����� 1��#��ݣ� 2��#���ȣ� 3��#�·ݣ� 4��#�ܣ� 5��#�գ� 6��#Сʱ�� 7��#���ӣ� 8��#�롣
*/
double GetWeekDayNum(DATE dt)
{
	double nRet;
	INT nSgn = dt > 0 ? 1:-1;
	//dt--;
	nRet = dt / 7;
	if(nRet !=0 && modf(nRet,&nRet) !=0)
		nRet +=nSgn;
	return nRet;
}

LIBAPI(void, krnln_TimeDiff)
{
	PMDATA_INF pArgInf = &ArgInf;
	switch(pArgInf[2].m_int)
	{
	case 1://#���
		{
			DATE objDate;
			INT nYear, nMonth, nDay;
			INT nYear1, nMonth1, nDay1;
			DATE dt = modf(pArgInf[0].m_date,&objDate);
			GetDatePart(objDate,nYear, nMonth, nDay);
			dt = modf(pArgInf[1].m_date,&objDate);
			GetDatePart(objDate,nYear1, nMonth1, nDay1);
			pArgInf[0].m_date = nYear - nYear1;
			break;
		}
	case 2://#����
		{
			DATE objDate;
			INT nYear, nMonth, nDay;
			INT nYear1, nMonth1, nDay1;
			DATE dt = modf(pArgInf[0].m_date,&objDate);
			GetDatePart(objDate,nYear, nMonth, nDay);
			dt = modf(pArgInf[1].m_date,&objDate);
			GetDatePart(objDate,nYear1, nMonth1, nDay1);

			objDate = (nYear*12+nMonth) - (nYear1*12+nMonth1);
			objDate = objDate / 3;
			dt = modf(objDate,&pArgInf[0].m_date);
			if(dt !=0)
				pArgInf[0].m_date ++;
			break;
		}
	case 3://#�·�
		{
			DATE objDate;
			INT nYear, nMonth, nDay;
			INT nYear1, nMonth1, nDay1;
			DATE dt = modf(pArgInf[0].m_date,&objDate);
			GetDatePart(objDate,nYear, nMonth, nDay);
			dt = modf(pArgInf[1].m_date,&objDate);
			GetDatePart(objDate,nYear1, nMonth1, nDay1);

			pArgInf[0].m_date = (nYear*12+nMonth) - (nYear1*12+nMonth1);
			break;
		}
	case 4://#��
		{
			DATE objDate, objDate1;
			DATE dt = modf(pArgInf[0].m_date,&objDate);
			dt = modf(pArgInf[1].m_date,&objDate1);

			pArgInf[0].m_date =GetWeekDayNum(objDate) - GetWeekDayNum(objDate1);
			break;
		}
	case 5://#��
		{

			DATE objDate = pArgInf[0].m_date - pArgInf[1].m_date;
			pArgInf[0].m_date = objDate;
			break;
		}
	case 6://#Сʱ
		{
			DATE objDate = pArgInf[0].m_date - pArgInf[1].m_date;
			double nSecCount = 86400 * objDate;//������
			objDate = nSecCount / 3600; //�����Сʱ
			pArgInf[0].m_date =objDate;
			break;
		}
	case 7://#����
		{
			DATE objDate = pArgInf[0].m_date - pArgInf[1].m_date;
			double nSecCount = 86400 * objDate;//������
			objDate = nSecCount / 60; //�����Сʱ
			pArgInf[0].m_date =objDate;
			break;
		}
	case 8://#�롣
		{
			DATE objDate = pArgInf[0].m_date - pArgInf[1].m_date;
			double nSecCount = 86400 * objDate;//������
			pArgInf[0].m_date = nSecCount;
			break;
		}
	default:
		pArgInf[0].m_double = 0;

	}
	__asm{
		mov eax, ArgInf.m_unit.m_dwFormID;
		mov edx, ArgInf.m_unit.m_dwUnitID;
	}

}
