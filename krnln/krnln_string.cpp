#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - ȡ�ظ��ı�
/*
    ���ø�ʽ�� ���ı��͡� ȡ�ظ��ı� �������� �ظ��������ı��� ���ظ��ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�string
    ����һ���ı������а���ָ���������ı��ظ������������Ϊ�������
    ����<1>������Ϊ���ظ�������������Ϊ�������ͣ�int������
    ����<2>������Ϊ�����ظ��ı���������Ϊ���ı��ͣ�text���������ı������ڽ������ص��ı������Ϊ�գ�������һ�����ı���
*/
LIBAPI(char*, krnln_string)
{
	PMDATA_INF pArgInf = &ArgInf;
	INT nLen = mystrlen(pArgInf[1].m_pText);
	if(nLen == 0 || ArgInf.m_int <=0 ) return NULL;

	INT nBuf = nLen * ArgInf.m_int;
	char *pText = (char*)E_MAlloc_Nzero(nBuf+1);
	char* pDest = pText;
	for(INT i=0;i< ArgInf.m_int;i++)
	{
		strncpy(pDest,pArgInf[1].m_pText,nLen);
		pDest+=nLen;
	}
	*pDest = 0;
	return pText;
}
