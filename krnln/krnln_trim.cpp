#include "stdafx.h"

//�ı����� - ɾ��β��
/*
    ���ø�ʽ�� ���ı��͡� ɾ��β�� ���ı��� ��ɾ���ո���ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�trim
    ����һ���ı������а�����ɾ�����ײ���β��ȫ�ǻ��ǿո��ָ���ı���������Ϊ�������
    ����<1>������Ϊ����ɾ���ո���ı���������Ϊ���ı��ͣ�text������
*/
LIBAPI(char*, krnln_trim)
{
	PMDATA_INF pArgInf = &ArgInf;
	char* pSrc = pArgInf[0].m_pText;
	register char *str1 = pSrc;

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
	if (!*str1) return NULL; //���ı�ֱ�ӷ���
	pSrc = str1;
	//β��
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
// {
// 	char *pText = krnln_LTrim(1,ArgInf);
// 	if(pText==NULL)return NULL;
// 
// 	INT nLen = strlen(pText);
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
// 	nLen = strlen(pText);
// 	if(nLen == 0)
// 	{
// 		E_MFree(pText);
// 		pText = NULL;
// 	}
// 	return pText;
// }
