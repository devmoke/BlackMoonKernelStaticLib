#include "stdafx.h"
#include "Myfunctions.h"

//�ı����� - ����д
/*
    ���ø�ʽ�� ���ı��͡� ����д ���ı��� ���任���ı��� - ϵͳ����֧�ֿ�->�ı�����
    Ӣ�����ƣ�UCase
    ���ı��е�СдӢ����ĸ�任Ϊ��д�����ر任��Ľ���ı���������Ϊ�������
    ����<1>������Ϊ�����任���ı���������Ϊ���ı��ͣ�text������
*/
LIBAPI(char*, krnln_UCase)
{// �����ߺŸ�
	register char* pSrc = ArgInf.m_pText;
	UINT nLen = mystrlen(pSrc);
	if (nLen==0) return NULL;
	char *pText = (char*)E_MAlloc_Nzero(nLen+1);
	register char* pDes = pText;
	register unsigned char* ut = uptable;
	for (UINT i=0; i<nLen; i++)
	{
		if (pSrc[i]<0)
		{
			*((short*)(pDes+i)) = *((short*)(pSrc+i));
			i++;
		}
		else
		{
			pDes[i] = ut[(unsigned char)(pSrc[i])];
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
// 			pText[i] = toupper(pText[i]);
// 			i++;
// 		}
// 
// 	}
// 	return pText;	
// }
