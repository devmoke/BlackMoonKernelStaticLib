#include "stdafx.h"
#include <math.h>
#include "Myfunctions.h"

//��ֵת�� - ��ֵ����д 
/*
    ���ø�ʽ�� ���ı��͡� ��ֵ����� ��˫����С���� ��ת����ʽ����ֵ���߼��� �Ƿ�ת��Ϊ���壩 - ϵͳ����֧�ֿ�->��ֵת��
    Ӣ�����ƣ�NumToRMB
    ����ֵת��Ϊ���ļ�������д��ʽ������ת������ı���������Ϊ�������
    ����<1>������Ϊ����ת����ʽ����ֵ��������Ϊ��˫����С���ͣ�double������
    ����<2>������Ϊ���Ƿ�ת��Ϊ���塱������Ϊ���߼��ͣ�bool��������ʼֵΪ���١����������ֵΪ�٣���ת��Ϊ���塣
*/
LIBAPI(char*, krnln_NumToRMB)
{
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[0].m_double<0)
		return NULL;
	double dInt;
	double dFloat = modf(pArgInf[0].m_double,&dInt);
	LPSTR pInt = NULL;
	LPSTR pFloat = NULL;
	INT nLen = 64;
	INT nPre=1;
	if(dInt !=0)
	{
		pInt = IntNumToChn(dInt,pArgInf[1].m_bool,nPre);
		nLen += mystrlen(pInt);
	}

	if(dFloat !=0)
	{
		pFloat = FloatNumToRMB(dFloat,pArgInf[1].m_bool);
		if(pFloat)
			nLen += mystrlen(pFloat);
	}
	
	LPSTR pText = (LPSTR)E_MAlloc (nLen);
	if(pFloat==NULL && pInt==NULL)
	{
		strcpy(pText,"��");
		return pText;
	}
	*pText=0;//MessageBox(NULL,pText,NULL,MB_OK);
	if(pInt)
	{
		strcpy(pText,pInt);
		free(pInt);
		strcat(pText,"Ԫ");
	}

	if(pFloat && *pFloat)
	{
		if(pInt && nPre==0)
			strcat(pText,"��");
		strcat(pText,pFloat);
		free(pFloat);
	}
	else
		strcat(pText,"��");

	return pText;	
}
