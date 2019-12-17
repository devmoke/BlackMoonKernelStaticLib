#include "stdafx.h"
#include "Myfunctions.h"

//���̲��� - ȡ���̾��
/*
    ���ø�ʽ�� ���ı��͡� ȡ���̾�� �����ı��� �����������ַ��ݣ� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�GetDiskLabel
    ����ָ�����̵ľ���ı���������Ϊ�������
    ����<1>������Ϊ�������������ַ���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ����ơ�A������B������C���ȣ�ֻȡ�ø����ı��ĵ�һ���ַ��������������ʡ�ԣ�Ĭ��ʹ�õ�ǰ��������

*/
LIBAPI(char*, krnln_GetDiskLabel)
{
	char DirName [MAX_PATH];
	if(ArgInf.m_dtDataType == _SDT_NULL)
	{
		if(GetCurrentDirectory(MAX_PATH,DirName)==0)
			return NULL;
		DirName[3]=0;

	}
	else
	{
		if(mystrlen(ArgInf.m_pText)==0)
			return NULL;

		DirName[0]=*ArgInf.m_pText;
		DirName[1]=':';
		DirName[2]='\\';
		DirName[3]=0;

	}

	char* pText = NULL;
	char strVolume [MAX_PATH];
	char FileSystemNameBuffer [64];
	DWORD VolumeSerialNumber;

	if(GetVolumeInformation(DirName,strVolume,MAX_PATH,
		&VolumeSerialNumber,
		NULL,
		NULL,
		FileSystemNameBuffer,
		64))
	{
		INT nLen = mystrlen(strVolume);
		pText = CloneTextData(strVolume,nLen);

	}
	return pText;
}
