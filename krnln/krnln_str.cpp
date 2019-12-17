#include "stdafx.h"
#include <stdio.h>
#include "LTrimZeroChr.h"
#include "Myfunctions.h"

//#pragma comment(lib,"oleaut32.lib") 

//�ı����� - ���ı�
/*
    ���ø�ʽ�� ���ı��͡� ���ı� ��ͨ��������/������ ��ת�������ݣ� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�str
    ����һ���ı�������ָ����ֵ���߼�ֵ������ʱ�䱻ת����Ľ�������Ϊ�ı����ݣ�����ֱ�ӷ��ء�������Ϊ�������
    ����<1>������Ϊ����ת�������ݡ�������Ϊ��ͨ���ͣ�all�������ṩ��������ʱ����ͬʱ�ṩ�������������ݡ�����ֵֻ��Ϊ��ֵ���߼�ֵ���ֽڼ�������ʱ�����ֵ�����顣
*/
char * ArryToString(void* pArry,DWORD szData)
{
	DWORD dwSize;
	char* pText = (char*)GetAryElementInf(pArry,dwSize);
	if(dwSize==0)
		return NULL;
	INT nMax = dwSize * szData;
	for(INT i=0;i<nMax;i++)
	{
		if(pText[i]==0)
			break;
	}
	UINT nLen = i;

	if(nLen==0)return NULL;
	char* pNewText = (char*)E_MAlloc_Nzero(nLen+1);
	memcpy(pNewText,pText,nLen);
	pNewText[nLen] = 0;
	return pNewText;

}

LIBAPI(char*, krnln_str)
{

	char * pText = NULL;
	if((ArgInf.m_dtDataType & DT_IS_ARY) == DT_IS_ARY)//������
	{
		ArgInf.m_dtDataType &=~DT_IS_ARY; //ȥ�������־
		DWORD szData = 0;
		switch(ArgInf.m_dtDataType)
		{
		case SDT_BYTE:
			szData = sizeof(BYTE);
			break;
		case SDT_SHORT:
			szData = sizeof(SHORT);
			break;
		case SDT_INT64:
			szData = sizeof(INT64);
			break;
		case SDT_INT:
		case SDT_SUB_PTR:
			szData = sizeof(DWORD);
			break;
		}
		if(szData)
			pText = ArryToString(ArgInf.m_pAryData,szData);
	}
	else
	{
		char str [MAX_PATH];
		int nLen = 0;
		char* pSrc = NULL;

		switch(ArgInf.m_dtDataType)
		{
		case SDT_TEXT:
			nLen = mystrlen(ArgInf.m_pText);
			if(nLen)
				pSrc = ArgInf.m_pText;
			break;
		case SDT_BYTE:
			{
				INT nVal = ArgInf.m_byte;
				sprintf(str,"%d",nVal);
				nLen = mystrlen(str);
				pSrc = str;
			}
			break;
		case SDT_SHORT:
			{
				INT nVal = ArgInf.m_short;
				sprintf(str,"%d",nVal);
				nLen = mystrlen(str);
				pSrc = str;
			}
			break;
		case SDT_INT:
		case SDT_SUB_PTR:
			sprintf(str,"%d",ArgInf.m_int);
			nLen = mystrlen(str);
			pSrc = str;
			break;
		case SDT_INT64:
			sprintf(str,"%I64d",ArgInf.m_int64);
			nLen = mystrlen(str);
			pSrc = str;
			break;
		case SDT_FLOAT:
			sprintf(str,"%f",ArgInf.m_float);
			LTrimZeroChr(str);
			nLen = mystrlen(str);
			pSrc = str;
			break;
		case SDT_DOUBLE:
			sprintf(str,"%lf",ArgInf.m_double);
			LTrimZeroChr(str);
			nLen = mystrlen(str);
			pSrc = str;
			break;
		case SDT_BOOL:
			if(ArgInf.m_bool)
				strcpy(str,"��");
			else
				strcpy(str,"��");
			nLen = mystrlen(str);
			pSrc = str;
			break;
		case SDT_BIN:
			pText = ArryToString(ArgInf.m_pBin,sizeof(BYTE));
			break;
		case SDT_DATE_TIME:
			DateTimeFormat(str,ArgInf.m_double);
			nLen = mystrlen(str);
			if(nLen)
				pSrc = str;
			break;
		}
		if(pSrc && nLen)
		{
			pText = (char*)E_MAlloc_Nzero(nLen+1);
			strcpy(pText,pSrc);
		}

	}
	return pText;
}
