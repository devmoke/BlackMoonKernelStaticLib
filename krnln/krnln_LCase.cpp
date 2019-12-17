#include "stdafx.h"
#include "Myfunctions.h"
//�ı����� - ��Сд
/*
    ���ø�ʽ�� ���ı��͡� ��Сд ���ı��� ���任���ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�LCase
    ���ı��еĴ�дӢ����ĸ�任ΪСд�����ر任��Ľ���ı���������Ϊ�������
    ����<1>������Ϊ�����任���ı���������Ϊ���ı��ͣ�text������
*/
LIBAPI(char*, krnln_LCase)
{// �����ߺŸ�
	register char* pSrc = ArgInf.m_pText;
	UINT nLen = mystrlen(pSrc);
	if (nLen==0) return NULL;
	char *pText = (char*)E_MAlloc_Nzero(nLen+1);
	register char* pDes = pText;
	register unsigned char* ltb = lowtable;
	for (UINT i=0; i<nLen; i++)
	{
		if (pSrc[i]<0)
		{
			*((short*)(pDes+i)) = *((short*)(pSrc+i));
			i++;
		}
		else
		{
			pDes[i] = ltb[(unsigned char)(pSrc[i])];
		}
	}
	pText[nLen] = '\0';
	return pText;
}
// {// ����ԭ��
// 	UINT nLen = strlen(ArgInf.m_pText);
// 	if(nLen==0)return NULL;
// 	char *pText = (char*)E_MAlloc(nLen+1);
// 	strcpy(pText,ArgInf.m_pText);
// 	UINT i=0;
// 	while(i < nLen)
// 	{
// 		if(pText[i]<0)
// 			i+=2;//����
// 		else
// 		{
// 			pText[i] = tolower(pText[i]);
// 			i++;
// 		}
// 
// 	}
// 	return pText;	
// }
