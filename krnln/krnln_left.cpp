#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - ȡ�ı����
/*
    ���ø�ʽ�� ���ı��͡� ȡ�ı���� ���ı��� ��ȡ�䲿�ֵ��ı��������� ��ȡ���ַ�����Ŀ�� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�left
    ����һ���ı������а���ָ���ı��д��������ָ���������ַ���������Ϊ�������
    ����<1>������Ϊ����ȡ�䲿�ֵ��ı���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ����ȡ���ַ�����Ŀ��������Ϊ�������ͣ�int������
*/
LIBAPI(char*, krnln_left)
{
	PMDATA_INF pArgInf = &ArgInf;
	INT nLen = mystrlen(ArgInf.m_pText);
	if(nLen==0 || pArgInf[1].m_int <=0)return NULL;

	if(pArgInf[1].m_int < nLen)
		nLen = pArgInf[1].m_int;

	char *pText = (char*)E_MAlloc_Nzero(nLen+1);
	memcpy(pText,ArgInf.m_pText,nLen);
	pText[nLen]=0;
	return pText;	

}
