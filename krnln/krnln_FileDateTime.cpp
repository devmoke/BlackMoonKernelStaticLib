#include "stdafx.h"
#include <SHLWAPI.h>
#pragma comment(lib,"SHLWAPI.lib") 
//���̲��� - ȡ�ļ�ʱ��
/*
    ���ø�ʽ�� ������ʱ���͡� ȡ�ļ�ʱ�� ���ı��� �ļ����� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�FileDateTime
    ����ָ���ļ�������������޸ĺ�����ں�ʱ�䡣������ļ������ڣ�������100��1��1�ա�������Ϊ�������
    ����<1>������Ϊ���ļ�����������Ϊ���ı��ͣ�text������
	FileTimeToLocalFileTime
	FileTimeToSystemTime 

*/
LIBAPI(void, krnln_FileDateTime) //ֱ���޸���eax��edx��������ָ������ֵ����
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(ArgInf.m_pText, &FindFileData);
	ArgInf.m_date =  -657434;//100��1��1��
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		if(FileTimeToLocalFileTime(&FindFileData.ftLastWriteTime,&FindFileData.ftCreationTime))
		{
			SYSTEMTIME now;
			if(FileTimeToSystemTime (&FindFileData.ftCreationTime,&now))
				ArgInf.m_double = GetSpecDateTime(now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
		}
	}
	__asm{
		mov eax, ArgInf.m_unit.m_dwFormID;
		mov edx, ArgInf.m_unit.m_dwUnitID;
	}
}
// {//����ԭ��
// 	HANDLE hFile = CreateFile(ArgInf.m_pText,
// 		GENERIC_READ,
// 		FILE_SHARE_READ|FILE_SHARE_WRITE,
// 		NULL,
// 		OPEN_EXISTING,
// 		FILE_ATTRIBUTE_ARCHIVE,
// 		0);
// 
// 	ArgInf.m_date =  -657434;//100��1��1��
// 	if(hFile != INVALID_HANDLE_VALUE)
// 	{
// 		FILETIME CreationTime,LastWriteTime;
// 		BOOL bRet = GetFileTime(hFile,&CreationTime,NULL,&LastWriteTime);
// 		CloseHandle(hFile);
// 		if(bRet)
// 		{
// 			if(FileTimeToLocalFileTime(&LastWriteTime,&CreationTime))
// 			{
// 				SYSTEMTIME now;
// 				if(FileTimeToSystemTime (&CreationTime,&now))
// 					ArgInf.m_double = GetSpecDateTime(now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond);
// 
// 			}
// 
// 
// 		}
// 
// 	}
// 		
// 
// 	__asm{
// 		mov eax, ArgInf.m_unit.m_dwFormID;
// 		mov edx, ArgInf.m_unit.m_dwUnitID;
// 	}
// }
