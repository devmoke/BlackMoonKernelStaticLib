#include "stdafx.h"
#include <stdio.h>
#include <math.h>

//��ʽ��ʱ���ı�
void DateTimeFormat(LPSTR strValue,DATE dtDt,BOOL bOnlyDatePart)
{
	DATE dd,dt;
	INT nYear, nMonth, nDay, nHour, nMinute, nSecond;
	dt = modf(dtDt,&dd);


	GetTimePart(dt,nHour,nMinute,nSecond);
	GetDatePart(dd,nYear,nMonth,nDay);


	char strFormat [128];
	strcpy(strFormat,"%d��%d��%d��");


	//��ʽ��ʱ�䲿��
	char strFormatTime [128];
	
	if(nSecond)
		strcpy(strFormatTime,"%dʱ%d��%d��");
	else if(nMinute && nSecond ==0)
		strcpy(strFormatTime,"%dʱ%d��");
	else if(nHour && nMinute==0 && nSecond ==0)
		strcpy(strFormatTime,"%dʱ");
	else
		strFormatTime[0]=0;

	if(bOnlyDatePart==FALSE)
		strcat(strFormat,strFormatTime);

	sprintf(strValue,strFormat,nYear, nMonth, nDay, nHour, nMinute, nSecond);

}