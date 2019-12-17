#include "stdafx.h"

//�ļ���д - ���ļ�
/*
    ���ø�ʽ�� �������͡� ���ļ� ���ı��� ���򿪵��ļ����ƣ��������� �򿪷�ʽ�ݣ��������� ����ʽ�ݣ� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�open
    ��һ����ͨ�ļ����Զ��ļ����������������ɹ����ر����ļ����ļ��ţ�ʧ�ܷ��� 0��������Ϊ�������
    ����<1>������Ϊ�����򿪵��ļ����ơ�������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ���򿪷�ʽ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵ˵�����ļ��Ĳ�����ʽ�����ʡ�Ա�������Ĭ��Ϊ��#��д������ʽֵ����Ϊ���³���֮һ��
  1��#���룺��ָ���ļ��������ݣ�������ļ���������ʧ�ܣ�
  2��#д����д�����ݵ�ָ���ļ���������ļ���������ʧ�ܣ�
  3��#��д�����ļ��ж������ݻ���д�����ݵ��ļ���������ļ���������ʧ�ܣ�
  4��#��д��д�����ݵ�ָ���ļ���������ļ����������ȴ���һ�����ļ�������Ѿ����ھ���������е��������ݣ�
  5��#��д��д�����ݵ�ָ���ļ���������ļ��������򴴽�һ�����ļ�������Ѿ����ھ�ֱ�Ӵ򿪣�
  6��#�Ķ������ļ��ж������ݻ���д�����ݵ��ļ���������ļ��������򴴽�һ�����ļ�������Ѿ����ھ�ֱ�Ӵ򿪡�
    ����<3>������Ϊ������ʽ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵָ�������������̲������ļ��ķ�ʽ�����ʡ�Ա�������Ĭ��Ϊ��#�����ơ�����ʽֵ����Ϊ���³���֮һ��
  1��#�����ƣ������������������д���ļ���
  2��#��ֹ������ֹ�������̶����ļ���
  3��#��ֹд����ֹ��������д���ļ���
  4��#��ֹ��д����ֹ�������̶�д���ļ���
*/
LIBAPI(void*, krnln_open)
{
	PMDATA_INF pArgInf = &ArgInf;
	DWORD dwDesiredAccess,dwShareMode,dwCreationDisposition;

	if(pArgInf[1].m_dtDataType == _SDT_NULL)
	{//#��д
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
	}
	else
	{
		switch (pArgInf[1].m_int)
		{
		case 1://#����
			dwDesiredAccess = GENERIC_READ;
			dwCreationDisposition = OPEN_EXISTING;
			break;
		case 2://#д��
			dwDesiredAccess = GENERIC_WRITE;
			dwCreationDisposition = OPEN_EXISTING;
			break;
		case 4://#��д
			dwDesiredAccess = GENERIC_WRITE;
			dwCreationDisposition = CREATE_ALWAYS;
			break;
		case 5://#��д
			dwDesiredAccess = GENERIC_WRITE;
			dwCreationDisposition = OPEN_ALWAYS;
			break;
		case 6://#�Ķ�
			dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			dwCreationDisposition = OPEN_ALWAYS;
			break;
		default://#��д
			dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
			dwCreationDisposition = OPEN_EXISTING;
			break;
		}
	}

	if(pArgInf[2].m_dtDataType == _SDT_NULL)
		dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE );
	else
	{
		if(pArgInf[2].m_int ==2)
			dwShareMode = FILE_SHARE_WRITE ;
		else if(pArgInf[2].m_int ==3)
			dwShareMode = FILE_SHARE_READ ;
		else if(pArgInf[2].m_int ==4)
			dwShareMode = 0;
		else
			dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE );
	}

	HANDLE hFile = CreateFile(ArgInf.m_pText,
		dwDesiredAccess,
		dwShareMode,
		NULL,
		dwCreationDisposition,
		FILE_ATTRIBUTE_ARCHIVE,
		0);
	

	if(hFile != INVALID_HANDLE_VALUE)
	{
		PFILEELEMENT pFile = new FILEELEMENT;
		pFile->nType = 1;
		pFile->FileHandle = hFile;
		AddFileMangerList(pFile);
		return pFile;
	}
	return NULL;
}

