#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - ɾȫ����
/*
    ���ø�ʽ�� ���ı��͡� ɾȫ���� ���ı��� ��ɾ���ո���ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�TrimAll
    ����һ���ı������а�����ɾ��������ȫ�ǻ��ǿո��ָ���ı���������Ϊ�������
    ����<1>������Ϊ����ɾ���ո���ı���������Ϊ���ı��ͣ�text������
*/
LIBAPI(char*, krnln_TrimAll)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	char* pSrc = pArgInf[0].m_pText;
	register char *str1 = pSrc;
	if (!*str1) return NULL;

	// ��ʼ����
	PINT pTb = (PINT)malloc(256);
	if (!pTb)
		return NULL;
	
	pTb[0] = 256; // TSize
	pTb[1] = 0; // Count
	pTb[2] = 0; // TLen
	char* pFirst = pSrc;
	while (1)
	{
		//�׿�
		while ( *str1 )
		{
			if (*str1 == ' ')
				str1++;
			else if (*((unsigned short*)str1) == 0xA1A1)
				str1+=2;
			else
				break;
		}
		if (!*str1) break;
		pFirst = str1;
		str1++;
		//��β
		while ( *str1 )
		{
			if (*str1 == ' ')
				break;
			else if (*((unsigned short*)str1) == 0xA1A1)
				break;
			if (*str1 < 0)
				str1++;
			str1++;
		}
		if (str1 - pFirst > 0)
			recSub(&pTb, (INT)pFirst, str1 - pFirst);
	}
	INT nLen = pTb[2];
	INT nCount = pTb[1];
	register PINT pTbtmp = pTb;
	pTbtmp+=3;
	char* pText = (char*)E_MAlloc_Nzero(nLen + 1);
	register char* pText2 = pText;
	for (int i=0; i < nCount; i++)
	{
		memcpy(pText2, (char*)(pTbtmp[0]), pTbtmp[1]);
		pText2 += pTbtmp[1];
		pTbtmp += 2;
	}
	pText[nLen] = '\0';
	if (pTb)
		free(pTb);
	return pText;
}
// {// ����ԭ��
// 	INT nLen = mystrlen(ArgInf.m_pText);
// 	if(nLen==0)return NULL;
// 	char *pText = (char*)E_MAlloc_Nzero(nLen+1);
// 
// 	INT i = 0;
// 	char* pSrc = ArgInf.m_pText;
// 	char* pStart ;//= ArgInf.m_pText;
// 	char* pDest = pText;
// 	while(i < nLen)
// 	{
// 		while(*pSrc == ' ' || strncmp(pSrc,"��",2)==0)
// 		{
// 
// 			if(*pSrc< 0)
// 			{
// 				i+=2;
// 				pSrc+=2;
// 			}
// 			else
// 			{
// 				pSrc++;
// 				i++;
// 			}
// 		}
// 		pStart = pSrc;
// 
// 		while(*pSrc != 0 && *pSrc != ' ' && strncmp(pSrc,"��",2)!=0)
// 		{
// 			if(*pSrc< 0)
// 			{
// 				i+=2;
// 				pSrc+=2;
// 			}
// 			else
// 			{
// 				pSrc++;
// 				i++;
// 			}
// 		}
// 		DWORD dwLen = pSrc - pStart;
// 		if(dwLen)
// 		{
// 			strncpy(pDest,pStart,dwLen);
// 			pDest+=dwLen;
// 		}
// 		if(*pSrc == 0)
// 			break;
// 	}
// 	*pDest = 0;
// 	nLen = mystrlen(pText);
// 	if(nLen == 0)
// 	{
// 		E_MFree(pText);
// 		pText = NULL;
// 	}
// 	return pText;
// }
