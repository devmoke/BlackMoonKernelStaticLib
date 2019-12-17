#include "stdafx.h"

#define VER_NT_WORKSTATION              0x0000001
#define VER_NT_DOMAIN_CONTROLLER        0x0000002
#define VER_NT_SERVER                   0x0000003
typedef   struct   OSVERSIONINFOEX1
{ 
	DWORD   dwOSVersionInfoSize; 
	DWORD   dwMajorVersion; 
	DWORD   dwMinorVersion; 
	DWORD   dwBuildNumber; 
	DWORD   dwPlatformId; 
	WCHAR     szCSDVersion[128];           //   Maintenance   string   for   PSS   usage
	WORD       wServicePackMajor; 
	WORD       wServicePackMinor; 
	WORD       wSuiteMask; 
	BYTE     wProductType; 
	BYTE     wReserved; 
}   OSVERSIONINFOEXW1; 

//ϵͳ���� - ȡ����ϵͳ���
/*
    ���ø�ʽ�� �������͡� ȡ����ϵͳ��� ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetSysVer
    ���ص�ǰ����ϵͳ�İ汾��𡣷���ֵΪ����ֵ֮һ��0��δ֪�� 1��Windows 32S�� 2��Windows 9X (����Win95��Win98��WinME��)�� 3��Windows NT (����WinNT��Win2000��WinXP��)�� 4��Linux��������Ϊ�������
*/
LIBAPI(int, krnln_GetSysVer)
{
	OSVERSIONINFO VersionInformation;
	INT nRet = 0;
	memset(&VersionInformation,0,sizeof(OSVERSIONINFO));
	VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if(GetVersionEx(&VersionInformation))
	{
		switch(VersionInformation.dwPlatformId)
		{
		case VER_PLATFORM_WIN32s:
			nRet = 1;
			break;
		case VER_PLATFORM_WIN32_WINDOWS:
			nRet = 2;
			break;
		case VER_PLATFORM_WIN32_NT:
			nRet = 3;
			break;
		}

	}
	return nRet;

}


//ϵͳ���� - ȡ����ϵͳ���2
/*
    ���ø�ʽ�� �������͡� ȡ����ϵͳ���2 ���� - ϵͳ����֧�ֿ�->ϵͳ����
    Ӣ�����ƣ�GetSysVer2
    ���ص�ǰ����ϵͳ�İ汾��𡣷���ֵΪ����ֵ֮һ��0��δ֪�� 1��Windows 32S�� 2��Windows 9X (����Win95��Win98��WinME��)�� 3������Windows NT����ϵͳ(�����������г���)�� 
	4��Linux�� 5��Windows 10�� 6��Windows Server 2016 Technical Preview�� 7��Windows 8.1�� 8��Windows Server 2012 R2�� 9��Windows 8�� 10��Windows Server 2012�� 
	11��Windows 7�� 12��Windows Server 2008 R2�� 13��Windows Server 2008�� 14��Windows Vista��������Ϊ�������
*/

LIBAPI(int, krnln_GetSysVer2)
{
	OSVERSIONINFOEX1 VerInfoEx;
	INT nRet = 0;
	memset(&VerInfoEx,0,sizeof(OSVERSIONINFOEX1));
	VerInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX1);
	if(GetVersionEx((OSVERSIONINFO*)&VerInfoEx))
	{
		switch(VerInfoEx.dwPlatformId)
		{
		case VER_PLATFORM_WIN32s:
			nRet = 1; //Windows 32S
			break;
		case VER_PLATFORM_WIN32_WINDOWS:
			nRet = 2; //Windows 9X (����Win95��Win98��WinME��)
			break;
		case VER_PLATFORM_WIN32_NT:
			switch (VerInfoEx.dwMajorVersion)
			{
			case 10:
				if (VerInfoEx.wProductType==VER_NT_WORKSTATION)
					nRet = 5; //Windows 10
				else
					nRet = 6; //Windows Server 2016 Technical Preview
			
				break;
			case 6:
				switch (VerInfoEx.dwMinorVersion)
				{
				case 3:
					if (VerInfoEx.wProductType==VER_NT_WORKSTATION)
						nRet = 7; //Windows 8.1
					else
						nRet = 8; //Windows Server 2012 R2
				
					break;
				case 2:
					if (VerInfoEx.wProductType==VER_NT_WORKSTATION)
						nRet = 9; //Windows 8
					else
						nRet = 10; //Windows Server 2012

					break;
				case 1:
					if (VerInfoEx.wProductType==VER_NT_WORKSTATION)
						nRet = 11; //Windows 7
					else
						nRet = 12; //Windows Server 2008 R2

					break;
				default:
					if (VerInfoEx.wProductType==VER_NT_WORKSTATION)
						nRet = 14; //Windows Vista
					else
						nRet = 13; //Windows Server 2008

					break;
				}
				break;
			default:
				nRet = 3; //����Windows NT����ϵͳ(�����������г���)
				break;
			}
		}
	}
	return nRet;
}