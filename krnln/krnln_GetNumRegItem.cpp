#include "stdafx.h"
#include "Myfunctions.h"

#pragma comment(lib,"advapi32.lib") 
//ϵͳ���� - ȡ��ֵע����
/*
    ���ø�ʽ�� �������͡� ȡ��ֵע���� �������� ��Ŀ¼���ı��� ȫ·��ע���������������� Ĭ����ֵ�ݣ� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetNumRegItem
    �� Windows ע����з���ָ������ֵ����ע�����ֵ��������ȡע����Ĭ��ֵ��������Ŀ����ӡ�\���ţ��硰test\�����롰ȡ��ֵע�������ͬ���Ǳ��������ȡ����λ�ô���ע����������Ϊ�м����
    ����<1>������Ϊ����Ŀ¼��������Ϊ�������ͣ�int����������Ϊ���³���ֵ֮һ�� 1��#���ࣻ 2��#�������ã� 3��#�����û��� 4��#���ػ����� 5��#�����û���
    ����<2>������Ϊ��ȫ·��ע��������������Ϊ���ı��ͣ�text������
    ����<3>������Ϊ��Ĭ����ֵ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ����ָ����ע�������ڣ������ش�Ĭ����ֵ�����ָ����ע���������ұ�������ʡ�ԣ���������ֵ 0��
*/
LIBAPI(int, krnln_GetNumRegItem)
{
	PMDATA_INF pArgInf = &ArgInf;
	HKEY hRootkey = GetRegRootVal(pArgInf[0].m_int);
	BOOL bOk = FALSE;
	INT nRetVal = 0;
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
		
			DWORD nLen = 4;
			DWORD dwType = REG_DWORD;

			if(ERROR_SUCCESS == RegQueryValueEx(hkey,pKeyname,NULL,&dwType,(LPBYTE)&nRetVal,&nLen))
			{
				if(dwType == REG_DWORD)
					bOk = TRUE;
			}

			RegCloseKey(hkey);

		}
		delete [] pSubkey;
	}

	if(bOk == FALSE && pArgInf[2].m_dtDataType != _SDT_NULL)
	{
		nRetVal = pArgInf[2].m_int;
	}
	return nRetVal;
}
