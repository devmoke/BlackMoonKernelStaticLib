#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - ȡ�ı��ұ�
/*
    ���ø�ʽ�� ���ı��͡� ȡ�ı��ұ� ���ı��� ��ȡ�䲿�ֵ��ı��������� ��ȡ���ַ�����Ŀ�� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�right
    ����һ���ı������а���ָ���ı��д��ұ�����ָ���������ַ���������Ϊ�������
    ����<1>������Ϊ����ȡ�䲿�ֵ��ı���������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ����ȡ���ַ�����Ŀ��������Ϊ�������ͣ�int������
*/
LIBAPI(char*, krnln_right)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	INT nSubLen = pArgInf[1].m_int;
	if (nSubLen <= 0) 
		return NULL;
	INT nLen = mystrlen(ArgInf.m_pText);
	if (nLen == 0) 
		return NULL;
	if (nSubLen > nLen)
		nSubLen = nLen;
	char* pText = (char*)E_MAlloc_Nzero(nSubLen + 1);
	memcpy(pText, ArgInf.m_pText + (nLen - nSubLen), nSubLen + 1);
	return pText;
}
// {����ԭ��
// 	PMDATA_INF pArgInf = &ArgInf;
// 	UINT nLen = strlen(ArgInf.m_pText);
// 	if(nLen==0 || pArgInf[1].m_int <=0)return NULL;
// 
// 	INT nOffset = nLen - pArgInf[1].m_int;
// 	if(nOffset < 0)
// 		nOffset = 0;
// 	char* pSrc = ArgInf.m_pText + nOffset;
// 	nLen = strlen(pSrc);
// 
// 	char *pText = (char*)E_MAlloc(nLen+1);
// 	strcpy(pText,pSrc);
// 	return pText;	
// }
