#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - ɾβ��
/*
    ���ø�ʽ�� ���ı��͡� ɾβ�� ���ı��� ��ɾ���ո���ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�RTrim
    ����һ���ı������а�����ɾ����β��ȫ�ǻ��ǿո��ָ���ı���������Ϊ�������
    ����<1>������Ϊ����ɾ���ո���ı���������Ϊ���ı��ͣ�text������
*/
LIBAPI(char*, krnln_RTrim)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	char* pSrc = pArgInf[0].m_pText;
	register char *str1 = pSrc;
	
	register char* pLastNS = NULL;
	while ( *str1 )
	{
		if (*((unsigned short*)str1) == 0xA1A1)
			str1++;
		else
		{
			if (*str1 != ' ')
			{
				
				if (*str1 < 0)
				{
					pLastNS = str1 + 1;
					str1++;
				}else{
					pLastNS = str1;
				}
			}
		}
		str1++;
	}
	
	if (!pLastNS) return NULL; //���ı�ֱ�ӷ���
	INT nLen = pLastNS - pSrc + 1;
	char *pText = (char*)E_MAlloc_Nzero(nLen+1);
	memcpy(pText, pSrc, nLen);
	pText[nLen] = '\0';
	
	return pText;
}
// {//����ԭ��
// 	INT nLen = mystrlen(ArgInf.m_pText);
// 	if(nLen==0)return NULL;
// 	char *pText = (char*)E_MAlloc_Nzero(nLen+1);
// 	strcpy(pText,ArgInf.m_pText);
// 
// 	char* pSrc = pText + nLen - 1;
// 	while(pSrc >= pText)
// 	{
// 		if(*pSrc == ' ' || (*pSrc == -95 && *(pSrc-1) == -95))
// 		{
// 			if(*pSrc< 0)
// 			{
// 				pSrc-=2;
// 			}
// 			else
// 			{
// 				pSrc--;
// 			}
// 		}
// 		else
// 		{
// 			pSrc++;
// 			*pSrc = 0;
// 
// 			break;
// 		}
// 
// 	}
// 	nLen = mystrlen(pText);
// 	if(nLen == 0)
// 	{
// 		E_MFree(pText);
// 		pText = NULL;
// 	}
// 	return pText;
// 
// }
