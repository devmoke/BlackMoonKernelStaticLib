#include "stdafx.h"
#include "mem.h"
#include "Myfunctions.h"
//ϵͳ���� - ȡ���ý���
/*
    ���ø�ʽ�� ���ı������页 ȡ���ý��� ���ı��� �����ļ����� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetSectionNames
    ����ָ�������ļ����������н������ı����顣������Ϊ�������
    ����<1>������Ϊ�������ļ�����������Ϊ���ı��ͣ�text������ָ�������ļ������ƣ�ͨ����.ini��Ϊ�ļ�����׺��

*/
LIBAPI(void*, krnln_GetSectionNames)
{
	CMyDWordArray aryText;
#define   MAX_ALLSECTIONS   0x32000 
//	LPSTR pBuff = NULL;
	INT nLen = MAX_ALLSECTIONS;
//	do
//	{
//		pBuff = new char[nLen+1];
		char pBuff [MAX_ALLSECTIONS];
		INT nRet = GetPrivateProfileSectionNames(pBuff, MAX_ALLSECTIONS, ArgInf.m_pText);
				
//		if(nRet < nLen)
//		{
			if(nRet >0)
			{
				LPSTR pText = pBuff;
				LPSTR pEnd = pText + nRet;
				while(*pText !=0 && pText < pEnd)
				{
					nLen = mystrlen(pText);
					aryText.Add ((DWORD)CloneTextData (pText, nLen));
					pText+=(nLen+1);
				}

			}
			//delete[] pBuff;
			//break;
//		}
		//nLen = nRet;
//		delete[] pBuff;
//	}while(1);

	

	
	// �����±����������ݡ�
	INT nSize = aryText.GetDWordCount () * sizeof (DWORD);
	LPSTR p = (LPSTR)E_MAlloc_Nzero (sizeof (INT) * 2 + nSize);
	*(LPINT)p = 1;  // ����ά����
	*(LPINT)(p + sizeof (INT)) = aryText.GetDWordCount ();
	memcpy (p + sizeof (INT) * 2, aryText.GetPtr (), nSize);
	return  p;  // ��������д�ظ����������
}
