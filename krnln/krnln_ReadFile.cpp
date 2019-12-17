#include "stdafx.h"

//���̲��� - �����ļ�
/*
    ���ø�ʽ�� ���ֽڼ��� �����ļ� ���ı��� �ļ����� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�ReadFile
    ����һ���ֽڼ������а���ָ���ļ����������ݡ�������Ϊ�������
    ����<1>������Ϊ���ļ�����������Ϊ���ı��ͣ�text������
*/
LIBAPI(void*, krnln_ReadFile)
{
	HANDLE hFile = CreateFile(ArgInf.m_pText,
		GENERIC_READ,
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_ARCHIVE,
		0);
	LPBYTE pData = NULL;

	if(hFile != INVALID_HANDLE_VALUE)
	{

		DWORD dwNumOfByteRead;
		INT nLen = GetFileSize(hFile, &dwNumOfByteRead);
		pData =  (LPBYTE)E_MAlloc_Nzero(nLen+2*sizeof(INT));
		*(LPINT)pData = 1;
		*(LPINT)(pData + sizeof(INT)) = nLen;
		INT nRet = ReadFile(hFile, pData + 2*sizeof(INT), nLen, &dwNumOfByteRead, 0);
		CloseHandle(hFile);
	}
	return pData;
}
