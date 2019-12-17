#include "stdafx.h"
#include <math.h>
//ʱ����� - ����ʱ��
/*void GetDatePart(DATE dt,INT& nYear,INT& nMonth,INT& nDay)
    ���ø�ʽ�� ������ʱ���͡� ����ʱ�� ������ʱ���� ʱ�䣬������ �����Ӳ��֣������� ����ֵ�� - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�TimeChg
    ����һ��ʱ�䣬��һʱ�䱻���ϻ��ȥ��һ�μ��������ı���ʱ����Ч�����Զ������������Чʱ�䡣������Ϊ�������
    ����<1>������Ϊ��ʱ�䡱������Ϊ������ʱ���ͣ�date������
    ����<2>������Ϊ�������Ӳ��֡�������Ϊ�������ͣ�int����������ֵָ�����ӻ����ʱ�����һ���֣�����Ϊ���³�����
	1��#��ݣ� 2��#���ȣ� 3��#�·ݣ� 4��#�ܣ� 5��#�գ� 6��#Сʱ�� 7��#���ӣ� 8��#�롣
    ����<3>������Ϊ������ֵ��������Ϊ�������ͣ�int����������ڱ����Ӳ��ֵ����ӻ������ֵ��
*/
LIBAPI(void, krnln_TimeChg)
{
	PMDATA_INF pArgInf = &ArgInf;
	switch(pArgInf[1].m_int)
	{
	case 1://#���
		{
			DATE objDate;
			INT nYear, nMonth, nDay;
			INT nHour, nMinute, nSecond;
			DATE dt = modf(pArgInf[0].m_date,&objDate);
			GetDatePart(objDate,nYear, nMonth, nDay);
			GetTimePart(dt,nHour, nMinute, nSecond);
			nYear+=pArgInf[2].m_int;
			if(nMonth==2 && nDay ==29)
				nDay = GetDaysOfSpecMonth(nYear,2);
			pArgInf[0].m_date =GetSpecDateTime(nYear,nMonth,nDay,nHour, nMinute, nSecond);
			break;
		}
	case 2://#����
		{
			DATE objDate;
			INT nYear, nMonth, nDay;
			INT nHour, nMinute, nSecond;
			nHour = nMinute = nSecond =0;
			DATE dt = modf(pArgInf[0].m_date,&objDate);
			GetDatePart(objDate,nYear, nMonth, nDay);
			if(dt !=0)
				GetTimePart(dt,nHour, nMinute, nSecond);

			nMonth+=(pArgInf[2].m_int*3);
			if(nMonth>0)
			{
				nYear+=(nMonth/12);
				nMonth %= 12;
			}
			else
			{
				INT decYear = nMonth/12;
				if(nMonth % 12 !=0)
					decYear --;
				nYear+=decYear;
				nMonth = 12 + (nMonth % 12);
			}

			INT nMaxDay = GetDaysOfSpecMonth(nYear,nMonth);
			if(nDay > nMaxDay)
				nDay = nMaxDay;
			pArgInf[0].m_date =GetSpecDateTime(nYear,nMonth,nDay,nHour, nMinute, nSecond);
			break;
		}
	case 3://#�·�
		{
			DATE objDate;
			INT nYear, nMonth, nDay;
			INT nHour, nMinute, nSecond;
			nHour = nMinute = nSecond =0;
			DATE dt = modf(pArgInf[0].m_date,&objDate);
			GetDatePart(objDate,nYear, nMonth, nDay);
			if(dt !=0)
				GetTimePart(dt,nHour, nMinute, nSecond);

			nMonth+=pArgInf[2].m_int;
			if(nMonth>0)
			{
				if(nMonth > 12)
					nYear+=(nMonth/12);
				nMonth %= 12;
				if(nMonth ==0)
					nMonth = 12;

			}
			else
			{
				INT decYear = nMonth/12;
				if(nMonth % 12 !=0 || nMonth ==0)
					decYear --;
				nYear+=decYear;
				nMonth = 12 + (nMonth % 12);
			}

			INT nMaxDay = GetDaysOfSpecMonth(nYear,nMonth);
			if(nDay > nMaxDay)
				nDay = nMaxDay;
			pArgInf[0].m_date =GetSpecDateTime(nYear,nMonth,nDay,nHour, nMinute, nSecond);
			break;
		}
	case 4://#��
		{
			DATE objDate;
			DATE dt = modf(pArgInf[0].m_date,&objDate);
			objDate+=(7*pArgInf[2].m_int);
			objDate+=dt;
			pArgInf[0].m_date =objDate;
			break;
		}
	case 5://#��
		{

			DATE objDate;
			DATE dt = modf(pArgInf[0].m_date,&objDate);
			objDate+=pArgInf[2].m_int;
			objDate+=dt;
			pArgInf[0].m_date =objDate;
			break;
		}
	case 6://#Сʱ
		{

/*			DATE objDate;
			DATE dt = modf(pArgInf[0].m_date,&objDate);
			
			double nSecCount =86400 * fabs(dt);//������
			nSecCount +=(pArgInf[2].m_int*3600);
			INT nDay =  INT(nSecCount / 86400);
			nSecCount = fmod (fabs(nSecCount),86400);
			objDate +=nDay;
			dt = nSecCount/86400;
			double nSgn = objDate < 0 ? -1:1;
			
			pArgInf[0].m_date =(fabs(objDate)+dt)* nSgn;
			*/
			pArgInf[0].m_date +=double(pArgInf[2].m_int)/24;
			break;
		}
	case 7://#����
		{
/*
			DATE objDate;
			DATE dt = modf(pArgInf[0].m_date,&objDate);

			double nSecCount =86400 * fabs(dt);//������DATE( 86400 * fabs(dt)+0.5);
			nSecCount +=(pArgInf[2].m_int*60);
			INT nDay =  INT(nSecCount / 86400);
			nSecCount = fmod (fabs(nSecCount),86400);
			objDate +=nDay;
			dt = nSecCount/86400;
			double nSgn = objDate < 0 ? -1:1;
			
			pArgInf[0].m_date =(fabs(objDate)+dt)* nSgn;*/
			pArgInf[0].m_date +=double(pArgInf[2].m_int)/1440;
			break;
		}
	case 8://#�롣
		{
/*
			DATE objDate;
			DATE dt = modf(pArgInf[0].m_date,&objDate);

			double nSecCount = 86400 * fabs(dt);//������
			nSecCount +=pArgInf[2].m_int;
			INT nDay =  INT(nSecCount / 86400);
			nSecCount = fmod (fabs(nSecCount),86400);
			objDate +=nDay;
			dt = nSecCount/86400;
			double nSgn = objDate < 0 ? -1:1;
			
			pArgInf[0].m_date =(fabs(objDate)+dt)* nSgn;*/
			pArgInf[0].m_date +=double(pArgInf[2].m_int)/86400;
			break;
		}
	}
	__asm{
		mov eax, ArgInf.m_unit.m_dwFormID;
		mov edx, ArgInf.m_unit.m_dwUnitID;
	}

}
