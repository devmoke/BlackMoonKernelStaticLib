#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include "Myfunctions.h"

//ʱ����� - ʱ�䵽�ı�
/*
    ���ø�ʽ�� ���ı��͡� ʱ�䵽�ı� ������ʱ���� ��ת�����ı���ʱ�䣬�������� ת�����֣ݣ� - ϵͳ����֧�ֿ�->ʱ�����
    Ӣ�����ƣ�TimeToText
    ��ָ��ʱ��ת��Ϊ�ı������ء�������Ϊ�������
    ����<1>������Ϊ����ת�����ı���ʱ�䡱������Ϊ������ʱ���ͣ�date������
    ����<2>������Ϊ��ת�����֡�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵ����Ϊ���³�����
	1��#ȫ��ת���� 2��#���ڲ��֣� 3��#ʱ�䲿�֡����ʡ���˱�������Ĭ��Ϊ��#ȫ��ת������
*/
LIBAPI(char*, krnln_TimeToText)
{
	PMDATA_INF pArgInf = &ArgInf;
	char str[128];
	if(pArgInf[1].m_int==2)
	{
		DateTimeFormat(str,ArgInf.m_date,TRUE);

	}else if(pArgInf[1].m_int==3)
	{
		DATE dd,dt;
		INT nHour, nMinute, nSecond;
		dt = modf(ArgInf.m_date,&dd);
		GetTimePart(dt,nHour, nMinute, nSecond);
		sprintf(str,"%dʱ%d��%d��",nHour, nMinute, nSecond);

	}else{
		DateTimeFormat(str,ArgInf.m_date);
	}
	INT nLen = mystrlen(str);
	char* pText = (char*)E_MAlloc_Nzero(nLen+1);
	strcpy(pText,str);
	return pText;

}
