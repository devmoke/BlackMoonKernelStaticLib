#include "stdafx.h"
#include "Myfunctions.h"

//������ȡ - ȡ����Ŀ¼
/*
    ���ø�ʽ�� ���ı��͡� ȡ����Ŀ¼ ���� - ϵͳ����֧�ֿ�->������ȡ
    Ӣ�����ƣ�GetRunPath
    ȡ��ǰ��ִ�е��׳����ļ�������Ŀ¼��������Ϊ�������
*/
LIBAPI(char*, krnln_GetRunPath)
{
	char strFile[MAX_PATH];
	int nLen;

	if(::GetModuleFileName(NULL,strFile,MAX_PATH))
	{
		nLen = mystrlen(strFile);
		char* pFind = strFile+nLen;
		do{
			pFind --;
			if(*pFind == '\\')
			{
				*pFind = 0;
				break;
			}

		}while(pFind > strFile);
	}

	nLen = mystrlen(strFile);
	char *pText = (char*)E_MAlloc_Nzero(nLen+1);
	strcpy(pText,strFile);
	return pText;

}
