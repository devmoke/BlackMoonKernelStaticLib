#include "stdafx.h"
#include "Myfunctions.h"

//�ı����� - ɾ�׿�
/*
    ���ø�ʽ�� ���ı��͡� ɾ�׿� ���ı��� ��ɾ���ո���ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�LTrim
    ����һ���ı������а�����ɾ�����ײ�ȫ�ǻ��ǿո��ָ���ı���������Ϊ�������
    ����<1>������Ϊ����ɾ���ո���ı���������Ϊ���ı��ͣ�text������

*/
LIBAPI(char*, krnln_LTrim)
{// �����ߺ� ��
	PMDATA_INF pArgInf = &ArgInf;
	register unsigned char *str1 = (unsigned char*)pArgInf[0].m_pText;

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
	INT nLen = mystrlen((char*)str1);
	char *pText = (char*)E_MAlloc_Nzero(nLen+1);
	memcpy(pText, str1, nLen+1);
	
	return pText;
}
// {// ����ԭ��
// 	INT nLen = strlen(ArgInf.m_pText);
// 	if(nLen==0)return NULL;
// 	INT i = 0;
// 	char* pSrc = ArgInf.m_pText;
// 	while(i < nLen)
// 	{
// 		if(*pSrc == ' ' || strncmp(pSrc,"��",2)==0)
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
// 		else
// 			break;
// 
// 	}
// 	nLen = strlen(pSrc);
// 	if(nLen==0)return NULL;
// 
// 	char *pText = (char*)E_MAlloc(nLen+1);
// 	strcpy(pText,pSrc);
// 
// 	return pText;
// 
// }
