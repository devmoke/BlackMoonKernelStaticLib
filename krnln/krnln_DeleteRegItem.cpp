#include "stdafx.h"
#include "Myfunctions.h"
#pragma comment(lib,"advapi32.lib") 
//ϵͳ���� - ɾ��ע����
/*
    ���ø�ʽ�� ���߼��͡� ɾ��ע���� �������� ��Ŀ¼���ı��� ȫ·��ע�������� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�DeleteRegItem
    �� Windows ע�����ɾ��ָ��ע������ע���Ŀ¼������ɾ��ע����Ĭ��ֵ��������Ŀ����ӡ�\���ţ��硰test\�����ɹ������棬���򷵻ؼ١�ע����ɾ��Ŀ¼֮ǰ������ɾ����Ŀ¼�����е���Ŀ��������Ϊ�м����
    ����<1>������Ϊ����Ŀ¼��������Ϊ�������ͣ�int����������Ϊ���³���ֵ֮һ�� 1��#���ࣻ 2��#�������ã� 3��#�����û��� 4��#���ػ����� 5��#�����û���
    ����<2>������Ϊ��ȫ·��ע��������������Ϊ���ı��ͣ�text������
*/
LIBAPI(BOOL, krnln_DeleteRegItem)
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
		if(RegOpenKeyEx(hRootkey,pSubkey,0,KEY_ALL_ACCESS,&hkey)==ERROR_SUCCESS)
		{
			bRet = (RegDeleteValue(hkey,pKeyname)==ERROR_SUCCESS);
			RegCloseKey(hkey);
		}
		if(bRet == FALSE)
		{
			bRet = (RegDeleteKey(hRootkey,pArgInf[1].m_pText)==ERROR_SUCCESS);
		}

		delete [] pSubkey;
	}

	return bRet;
}
