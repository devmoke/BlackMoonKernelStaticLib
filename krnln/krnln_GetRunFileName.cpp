#include "stdafx.h"
#include "Myfunctions.h"

//������ȡ - ȡִ���ļ���
/*
    ���ø�ʽ�� ���ı��͡� ȡִ���ļ��� ���� - ϵͳ����֧�ֿ�->������ȡ
    Ӣ�����ƣ�GetRunFileName
    ȡ��ǰ��ִ�е��׳����ļ������ơ�������Ϊ�������
*/
LIBAPI(char*, krnln_GetRunFileName)
{
	char strFile[MAX_PATH];
	int nLen;
	char* pSrc = strFile;

	if(::GetModuleFileName(NULL,strFile,MAX_PATH))
	{
		nLen = mystrlen(strFile);
		char* pFind = strFile+nLen;
		do{
			pFind --;
			if(*pFind == '\\')
			{
				pSrc = pFind +1;
				break;
			}

		}while(pFind > strFile);
	}

	nLen = mystrlen(pSrc);
	char *pText = (char*)E_MAlloc_Nzero(nLen+1);
	strcpy(pText,pSrc);
	return pText;
}
