#include "stdafx.h"
#include "Myfunctions.h"

#pragma comment(lib,"advapi32.lib") 
//ϵͳ���� - ע�����Ƿ����
/*
    ���ø�ʽ�� ���߼��͡� ע�����Ƿ���� �������� ��Ŀ¼���ı��� ȫ·��ע�������� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�IsRegItemExist
    ���ָ��ע�������ڣ������棬���򷵻ؼ١��������ע�����Ƿ���Ĭ��ֵ��������Ŀ����ӡ�\���ţ��硰test\����������Ϊ�м����
    ����<1>������Ϊ����Ŀ¼��������Ϊ�������ͣ�int����������Ϊ���³���ֵ֮һ�� 1��#���ࣻ 2��#�������ã� 3��#�����û��� 4��#���ػ����� 5��#�����û���
    ����<2>������Ϊ��ȫ·��ע��������������Ϊ���ı��ͣ�text������
*/
LIBAPI(BOOL, krnln_IsRegItemExist)
{
	PMDATA_INF pArgInf = &ArgInf;
	HKEY hRootkey = GetRegRootVal(pArgInf[0].m_int);
	BOOL bRet = FALSE;
	INT nLen = mystrlen(pArgInf[1].m_pText);
	if(hRootkey && nLen)
	{
		HKEY hkey;
		LPSTR pSubkey = new char [nLen +1];
		strcpy(pSubkey,pArgInf[1].m_pText);
		LPSTR pKeyname = strrchr(pSubkey,'\\');
		if(pKeyname)
		{
			*pKeyname = 0;
			pKeyname++;
		}
		if(RegOpenKey(hRootkey,pSubkey,&hkey)==ERROR_SUCCESS)
		{
			DWORD nLen = MAX_PATH;
			DWORD dwType;
			char sRetVal[MAX_PATH];
			INT nRet = RegQueryValueEx(hkey,pKeyname,NULL,&dwType,(LPBYTE)sRetVal,&nLen);
			if(ERROR_SUCCESS == nRet || nRet == ERROR_MORE_DATA)
			{
				bRet = TRUE;
			}
			RegCloseKey(hkey);
		}
		delete [] pSubkey;
	}

	return bRet;
}
