#include "stdafx.h"
#include "Myfunctions.h"

//���̲��� - ȡ����ʣ��ռ�
/*
    ���ø�ʽ�� �������͡� ȡ����ʣ��ռ� �����ı��� �����������ַ��ݣ� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�GetDiskFreeSpace
    ������ 1024 �ֽڣ�KB��Ϊ��λ��ָ����������ʣ��ռ䡣���ʧ�ܣ�����-1��������Ϊ�������
    ����<1>������Ϊ�������������ַ���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ����ơ�A������B������C���ȣ�ֻȡ�ø����ı��ĵ�һ���ַ��������������ʡ�ԣ�Ĭ��ʹ�õ�ǰ��������

*/
LIBAPI(int, krnln_GetDiskFreeSpace)
{
	char DirName [MAX_PATH];
	if(ArgInf.m_dtDataType == _SDT_NULL)
	{
		if(GetCurrentDirectory(MAX_PATH,DirName)==0)
			return -1;
		DirName[2]=0;

	}
	else
	{
		if(mystrlen(ArgInf.m_pText)==0)
			return -1;

		DirName[0]=*ArgInf.m_pText;
		DirName[1]=':';
		DirName[2]=0;

	}
	ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;

	if(GetDiskFreeSpaceEx(DirName,&FreeBytesAvailableToCaller,&TotalNumberOfBytes,&TotalNumberOfFreeBytes))
	{
		INT nRet = INT(FreeBytesAvailableToCaller.QuadPart/1024);
		return nRet;
	}
	return -1;
}
