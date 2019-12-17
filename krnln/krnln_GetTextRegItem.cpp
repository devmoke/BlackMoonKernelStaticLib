#include "stdafx.h"
#include "Myfunctions.h"
#pragma comment(lib,"advapi32.lib") 

//ϵͳ���� - ȡ�ı�ע����
/*
    ���ø�ʽ�� ���ı��͡� ȡ�ı�ע���� �������� ��Ŀ¼���ı��� ȫ·��ע�����������ı��� Ĭ���ı��ݣ� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetTextRegItem
    �� Windows ע����з���ָ�����ı�����ע�����ֵ��������ȡע����Ĭ��ֵ��������Ŀ����ӡ�\���ţ��硰test\�����롰ȡ�ı�ע�������ͬ���Ǳ��������ȡ����λ�ô���ע����������Ϊ�м����
    ����<1>������Ϊ����Ŀ¼��������Ϊ�������ͣ�int����������Ϊ���³���ֵ֮һ�� 1��#���ࣻ 2��#�������ã� 3��#�����û��� 4��#���ػ����� 5��#�����û���
    ����<2>������Ϊ��ȫ·��ע��������������Ϊ���ı��ͣ�text������
    ����<3>������Ϊ��Ĭ���ı���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ����ָ����ע�������ڣ������ش�Ĭ���ı������ָ����ע���������ұ�������ʡ�ԣ�������һ������Ϊ 0 �Ŀ��ı���
*/
LIBAPI(char*, krnln_GetTextRegItem)
{
	PMDATA_INF pArgInf = &ArgInf;
	HKEY hRootkey = GetRegRootVal(pArgInf[0].m_int);
	LPSTR pText = NULL;
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
		
			DWORD nLen = 1024;
			DWORD dwType = REG_SZ;
			INT nRet;
			LPSTR pData;
			do
			{
				pData = new char[nLen];

				nRet = RegQueryValueEx(hkey,pKeyname,NULL,&dwType,(LPBYTE)pData,&nLen);
				if(nRet == ERROR_SUCCESS)
				{
					if(dwType == REG_SZ || dwType == REG_EXPAND_SZ)
						pText = CloneTextData(pData,mystrlen(pData));
					break;

				}else if (nRet == ERROR_MORE_DATA)
				{
					delete [] pData;

				}else 	
					break;


			}while(1);

			delete [] pData;

			RegCloseKey(hkey);


		}
		delete [] pSubkey;
	}

	if(pText ==NULL && pArgInf[2].m_dtDataType != _SDT_NULL && pArgInf[2].m_pText)
	{
		pText = CloneTextData(pArgInf[2].m_pText,mystrlen(pArgInf[2].m_pText));
	}
	return pText;

}
