#include "stdafx.h"
#include <math.h>
#include <stdio.h>
//ȡ���ڲ���,����1Ϊֻ�����ڲ��ֵ�DATE����
//1899��12��30��0ʱ00��00�� Ϊ0��׼,��λΪ������С��ֵ

void GetDatePart(DATE dt,INT& nYear,INT& nMonth,INT& nDay)
{
	if(dt==0 || dt==1)
	{
		nYear = 1899;
		nMonth = 12;
		nDay = 30+dt;
		return;
	}
	INT nCountDay;
	INT nStatrYear;
	INT nYearDay;
	INT nStep;
	if(dt>0)
	{
		nCountDay = dt-1;//��1900��1��1��Ϊ��׼
		nStatrYear = 1900;
		nStep=1;
	}
	else
	{
		nCountDay = fabs(dt-1);//��1899��12��31��Ϊ��׼
		nStatrYear = 1899;
		nStep = -1;
	}

	while(1)
	{
		nYearDay = 365;
		if((nStatrYear % 400==0) || (nStatrYear % 100 !=0) && (nStatrYear %4 ==0))//����
			nYearDay ++;
		if(nCountDay <= nYearDay)//������ķ�Χ��
		{
			nYear = nStatrYear;
			if(nStep==-1)
			{
				nCountDay = nYearDay - nCountDay;
			}

			break;
		}
		nCountDay -=nYearDay;
		nStatrYear +=nStep;
	}
	DWORD nMonDay [12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if((nYear % 400==0) || (nYear % 100 != 0) && (nYear %4 ==0))//����
		nMonDay [1] = 29; //����

	for(INT i=0;i <12;i++)
	{
		if(nCountDay <= (INT)(nMonDay[i]))
		{
			nMonth = i+1;
			nDay = nCountDay;
			break;
		}
		nCountDay-=nMonDay[i];

	}
		
}

