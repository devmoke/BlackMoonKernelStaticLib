#include "stdafx.h"

//���̲��� - ȡ�ļ��ߴ�
/*
    ���ø�ʽ�� �������͡� ȡ�ļ��ߴ� ���ı��� �ļ����� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�FileLen
    ����һ���ļ��ĳ��ȣ���λ���ֽڡ�������ļ������ڣ������� -1��������Ϊ�������
    ����<1>������Ϊ���ļ�����������Ϊ���ı��ͣ�text������
*/
LIBAPI(int, krnln_FileLen)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(ArgInf.m_pText, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		if (FindFileData.nFileSizeHigh == 0xFFFFFFFF)
			return -1;
		return FindFileData.nFileSizeLow;
	}
	return -1;
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
// 	if(hFile == INVALID_HANDLE_VALUE)
// 		return -1;
// 	DWORD FileSizeLow,FileSizeHigh;
// 	FileSizeLow = GetFileSize(hFile,&FileSizeHigh);
// 	CloseHandle(hFile);
// 	if(0xFFFFFFFF == FileSizeHigh)
// 		return -1;
// 	return FileSizeLow;
// }
