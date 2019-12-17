#include "stdafx.h"
#include "Myfunctions.h"

//���̲��� - ȡ�����ܿռ�
/*
    ���ø�ʽ�� �������͡� ȡ�����ܿռ� �����ı��� �����������ַ��ݣ� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�GetDiskTotalSpace
    ������ 1024 �ֽڣ�KB��Ϊ��λ��ָ������ȫ���ռ䡣���ʧ�ܣ�����-1��������Ϊ�������
    ����<1>������Ϊ�������������ַ���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ����ơ�A������B������C���ȣ�ֻȡ�ø����ı��ĵ�һ���ַ��������������ʡ�ԣ�Ĭ��ʹ�õ�ǰ��������
*/
LIBAPI(int, krnln_GetDiskTotalSpace)
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
	//ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	DWORD SectorsPerCluster, BytesPerSector, NumberOfFreeClusters, nNumerator;

	if (GetDiskFreeSpace(DirName, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &nNumerator))
	{
		int nRet = int(MulDiv(BytesPerSector * SectorsPerCluster, nNumerator, 1024));
		return nRet;
	}
// 	if(GetDiskFreeSpaceEx(DirName,&FreeBytesAvailableToCaller,&TotalNumberOfBytes,&TotalNumberOfFreeBytes))
// 	{
// 		INT nRet = INT(TotalNumberOfBytes.QuadPart/1024);
// 		return nRet;
// 	}
	return -1;
}
