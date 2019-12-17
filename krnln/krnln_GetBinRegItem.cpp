#include "stdafx.h"
#include "Myfunctions.h"

#pragma comment(lib,"advapi32.lib") 
//ϵͳ���� - ȡ�ֽڼ�ע����
/*
    ���ø�ʽ�� ���ֽڼ��� ȡ�ֽڼ�ע���� �������� ��Ŀ¼���ı��� ȫ·��ע�����������ֽڼ� Ĭ���ֽڼ��ݣ� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetBinRegItem
    �� Windows ע����з���ָ�����ֽڼ�����ע�����ֵ��������ȡע����Ĭ��ֵ��������Ŀ����ӡ�\���ţ��硰test\�����롰ȡ�ֽڼ�ע�������ͬ���Ǳ��������ȡ����λ�ô���ע����������Ϊ�м����
    ����<1>������Ϊ����Ŀ¼��������Ϊ�������ͣ�int����������Ϊ���³���ֵ֮һ�� 1��#���ࣻ 2��#�������ã� 3��#�����û��� 4��#���ػ����� 5��#�����û���
    ����<2>������Ϊ��ȫ·��ע��������������Ϊ���ı��ͣ�text������
    ����<3>������Ϊ��Ĭ���ֽڼ���������Ϊ���ֽڼ���bin���������Ա�ʡ�ԡ����ָ����ע�������ڣ������ش�Ĭ���ֽڼ������ָ����ע���������ұ�������ʡ�ԣ������ؿ��ֽڼ���
*/
LIBAPI(void*, krnln_GetBinRegItem)
{
	PMDATA_INF pArgInf = &ArgInf;
	HKEY hRootkey = GetRegRootVal(pArgInf[0].m_int);
	LPBYTE pBin = NULL;
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
			DWORD dwType = REG_BINARY;
			INT nRet;
			LPBYTE pData;
			do
			{
				pData = new BYTE[nLen];

				nRet = RegQueryValueEx(hkey,pKeyname,NULL,&dwType,pData,&nLen);
				if(nRet == ERROR_SUCCESS)
				{
					if(dwType == REG_BINARY)
						pBin = CloneBinData(pData,nLen);
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

	if(pBin == NULL && pArgInf[2].m_dtDataType != _SDT_NULL && pArgInf[2].m_pBin)
	{
		pBin = CloneBinData(pArgInf[2].m_pBin+2*sizeof(INT),pArgInf[2].m_pInt[1]);
	}
	return pBin;
}
