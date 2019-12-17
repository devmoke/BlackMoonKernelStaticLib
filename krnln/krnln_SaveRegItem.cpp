#include "stdafx.h"
#pragma comment(lib,"advapi32.lib") 
#include "Myfunctions.h"

//ϵͳ���� - дע����
/*
    ���ø�ʽ�� ���߼��͡� дע���� �������� ��Ŀ¼���ı��� ȫ·��ע��������ͨ���� ��д��ֵ�� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�SaveRegItem
    �� Windows ע����б������ָ����ע��������д��ע����Ĭ��ֵ��������Ŀ����ӡ�\���ţ��硰test\�����ɹ������棬���򷵻ؼ١��롰дע�������ͬ���Ǳ��������д����λ�ô���ע����������Ϊ�м����
    ����<1>������Ϊ����Ŀ¼��������Ϊ�������ͣ�int����������Ϊ���³���ֵ֮һ�� 1��#���ࣻ 2��#�������ã� 3��#�����û��� 4��#���ػ����� 5��#�����û���
    ����<2>������Ϊ��ȫ·��ע��������������Ϊ���ı��ͣ�text������
    ����<3>������Ϊ����д��ֵ��������Ϊ��ͨ���ͣ�all����������ֵָ����д�뵽ָ��ע������е�ֵ��ֻ��Ϊ��ֵ���ı������ֽڼ����������ʧ�ܡ�
*/
LIBAPI(BOOL, krnln_SaveRegItem)
{
	PMDATA_INF pArgInf = &ArgInf;
	DWORD dwLen=0;
	DWORD dwType;
	DWORD dwNewVal;
	LPBYTE pData=NULL;

	switch(pArgInf[2].m_dtDataType)
	{
	case SDT_TEXT:
		dwType = REG_SZ;
		dwLen = mystrlen(pArgInf[2].m_pText)+1;
		pData = (LPBYTE)pArgInf[2].m_pText;
		break;
	case SDT_BIN:
		dwType = REG_BINARY;
		if(pArgInf[2].m_pBin)
		{
			dwLen = pArgInf[2].m_pInt[1];
			pData = pArgInf[2].m_pBin+2*sizeof(INT);
		}
		break;
	case SDT_INT:
	case SDT_BYTE:
	case SDT_SHORT:
		dwType = REG_DWORD;
		dwLen = sizeof(INT);
		pData = (LPBYTE)&pArgInf[2].m_int;
		break;
	case SDT_FLOAT:
		{
			dwType = REG_DWORD;
			dwLen = sizeof(INT);
			dwNewVal = pArgInf[2].m_float;
			//pArgInf[2].m_dwSubCodeAdr = dwVal;
			pData = (LPBYTE)&dwNewVal;
			break;
		}
	case SDT_INT64:
		{
			dwType = REG_DWORD;
			dwLen = sizeof(INT);
			dwNewVal = pArgInf[2].m_int64;
			//pArgInf[2].m_dwSubCodeAdr = dwVal;
			pData = (LPBYTE)&dwNewVal;
			break;
		}
	case SDT_DOUBLE:
		{
			dwType = REG_DWORD;
			dwLen = sizeof(INT);
			dwNewVal = pArgInf[2].m_double;
			//pArgInf[2].m_dwSubCodeAdr = dwVal;
			pData = (LPBYTE)&dwNewVal;
			break;
		}
	default:
		return FALSE;

	}

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
		if(RegCreateKeyEx(hRootkey,pSubkey,0,NULL,0,KEY_WRITE,NULL,&hkey,NULL)==ERROR_SUCCESS)
		{
			if(RegSetValueEx(hkey,pKeyname,0,dwType,pData,dwLen)==ERROR_SUCCESS)
			{
				bRet = TRUE;
			}
		

			RegCloseKey(hkey);


		}
		delete [] pSubkey;
	}

	return bRet;
}
