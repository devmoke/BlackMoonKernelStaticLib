#include "stdafx.h"
#include <stdio.h>
#include "LTrimZeroChr.h"
#include "Myfunctions.h"

//��ֵת�� - ��ֵ����ʽ�ı� 
/*
    ���ø�ʽ�� ���ı��͡� ��ֵ����ʽ�ı� ��˫����С���� ��ת��Ϊ�ı�����ֵ���������� С������λ���ݣ��߼��� �Ƿ����ǧ��λ�ָ��� - ϵͳ����֧�ֿ�->��ֵת��
    Ӣ�����ƣ�NumToText
    ����һ���ı�������ָ����ֵ����ʽת����Ľ����������Ϊ�������
    ����<1>������Ϊ����ת��Ϊ�ı�����ֵ��������Ϊ��˫����С���ͣ�double������
    ����<2>������Ϊ��С������λ����������Ϊ�������ͣ�int���������Ա�ʡ�ԡ��������0����ʾС�����ұ�Ӧ�������뱣����λ�����������0����ʾ���뵽���������С��0����ʾС����������뵽��λ�á����磺��ֵ����ʽ�ı� (1056.65, 1, ��) ���� ��1056.7���� ��ֵ����ʽ�ı� (1056.65, 0, ��) ���� ��1057���� ��ֵ����ʽ�ı� (1056.65, -1, ��) ���� ��1060�������ʡ�Ա���������Ĭ��Ϊ��������ʵ�ʴ��ڵ�С��λ��
    ����<3>������Ϊ���Ƿ����ǧ��λ�ָ���������Ϊ���߼��ͣ�bool��������ʼֵΪ���١����������ֵΪ�棬��ֵ�ı���ÿ��ǧ��λ�϶������Զ�����һ�����Ž��зָ���
*/
LIBAPI(char*, krnln_NumToText)
{
	PMDATA_INF pArgInf = &ArgInf;
	char str [MAX_PATH];
	char strFomar [MAX_PATH];
	if(pArgInf[1].m_dtDataType == _SDT_NULL)
	{
		strcpy(strFomar,"%lf");
		
	}
	else
	{
		INT nNum = pArgInf[1].m_int;
		if(nNum <0)
			nNum = 0;
		if(nNum>8)
			nNum = 8;
		sprintf(&strFomar[1],".%dlf",nNum);
		strFomar[0]='%';
	}

	sprintf(str,strFomar,ArgInf.m_double);
	if(pArgInf[1].m_dtDataType == _SDT_NULL)
		LTrimZeroChr(str);

	if(pArgInf[2].m_bool)
	{
		strcpy(strFomar,str);
		LPSTR pStr = strFomar;
		while(*pStr!=0 && *pStr !='.')
			pStr++;
		INT nNum = pStr - strFomar;
		pStr = strFomar;
		if(strFomar[0]=='-')
		{
			nNum--;
			pStr++;
		}
		if(nNum>3)
		{
			INT nMax = nNum/3;
			INT nMod = nNum % 3;
			if(nMod)
				nMax++;
			INT i = 0;
			LPSTR pSrc = strFomar;
			LPSTR pDest = str;
			
			while(i<nMax)
			{
				if(i==0 && nMod)
					pStr+=nMod;
				else
					pStr+=3;
				nNum = pStr - pSrc;
				
				if(i == nMax-1)
				{
					strcat(pDest,pSrc);
					break;
				}
				strncpy(pDest,pSrc,nNum);
				pDest+=nNum;
				*pDest=',';
				pDest++;
				*pDest=0;
				
				pSrc+=nNum;
				pStr=pSrc;
				i++;
				
			}
		}



	}
	INT nLen = mystrlen(str);
	char *pText = (char*)E_MAlloc(nLen+1);
	strcpy(pText,str);
	return pText;
}