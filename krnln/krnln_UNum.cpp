#include "stdafx.h"
#include <math.h>
#include "Myfunctions.h"

//��ֵת�� - ��ֵ����д 
/*
    ���ø�ʽ�� ���ı��͡� ��ֵ����д ��˫����С���� ��ת����ʽ����ֵ���߼��� �Ƿ�ת��Ϊ���壩 - ϵͳ����֧�ֿ�->��ֵת��
    Ӣ�����ƣ�UNum
    ����ֵת��Ϊ�������Ĵ�д��ʽ������ת������ı���������Ϊ�������
    ����<1>������Ϊ����ת����ʽ����ֵ��������Ϊ��˫����С���ͣ�double������
    ����<2>������Ϊ���Ƿ�ת��Ϊ���塱������Ϊ���߼��ͣ�bool��������ʼֵΪ���١����������ֵΪ�٣���ת��Ϊ���塣
*/
LIBAPI(char*, krnln_UNum)
{
	PMDATA_INF pArgInf = &ArgInf;
	double dInt;
	double dFloat = modf(pArgInf[0].m_double,&dInt);
	LPSTR pInt = NULL;
	LPSTR pFloat = NULL;
	INT nLen = 3;
	if(dInt !=0)
	{
		INT nPre=1;
		pInt = IntNumToChn(dInt,pArgInf[1].m_bool,nPre);
		nLen += mystrlen(pInt);
	}

	if(dFloat !=0)
	{
		pFloat = FloatNumToChn(dFloat,pArgInf[1].m_bool);
		if(pFloat)
			nLen += mystrlen(pFloat);
	}
	LPSTR pText = (LPSTR)E_MAlloc (nLen);
//	*pText=0;MessageBox(NULL,pText,NULL,MB_OK);
	if(pInt)
	{
		strcpy(pText,pInt);
		free(pInt);
	}else
		strcpy(pText,"��");

	if(pFloat)
	{
		strcat(pText,pFloat);
		free(pFloat);
	}

	return pText;	
}
