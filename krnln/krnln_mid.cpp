#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - ȡ�ı��м�
/*
    ���ø�ʽ�� ���ı��͡� ȡ�ı��м� ���ı��� ��ȡ�䲿�ֵ��ı��������� ��ʼȡ��λ�ã������� ��ȡ���ַ�����Ŀ�� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�mid
    ����һ���ı������а���ָ���ı��д�ָ��λ������ָ���������ַ���������Ϊ�������
    ����<1>������Ϊ����ȡ�䲿�ֵ��ı���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ����ʼȡ��λ�á�������Ϊ�������ͣ�int������1Ϊ��λ�ã�2Ϊ��2��λ�ã�������ơ�
    ����<3>������Ϊ����ȡ���ַ�����Ŀ��������Ϊ�������ͣ�int������
*/
LIBAPI(char*, krnln_mid)
{
	PMDATA_INF pArgInf = &ArgInf;
	if (pArgInf[1].m_int <=0 || pArgInf[2].m_int <= 0 ) return NULL;
	INT nLen = mystrlen(ArgInf.m_pText);
	if(nLen == 0) return NULL;
	//if(pArgInf[1].m_int <=0)
	//	pArgInf[1].m_int = 1;
	if(pArgInf[1].m_int > nLen)//��ʼλ�ò����ı���
		return NULL;

	INT nSubLen = pArgInf[1].m_int+pArgInf[2].m_int;
	if(nSubLen > nLen)
		nSubLen = nLen - pArgInf[1].m_int+1;
	else
		nSubLen = pArgInf[2].m_int;

	char* pSrc = ArgInf.m_pText + pArgInf[1].m_int - 1;

	char *pText = (char*)E_MAlloc_Nzero(nSubLen+1);
	memcpy(pText,pSrc,nSubLen);
	pText[nSubLen]=0;
	return pText;	

}
