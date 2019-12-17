#include "stdafx.h"
#include "MyMemFile.h"
//�ļ���д - �ƶ���дλ��
/*
    ���ø�ʽ�� ���߼��͡� �ƶ���дλ�� �������� �����в������ļ��ţ��������� ��ʼ�ƶ�λ�ãݣ������� �ƶ����룩 - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�FSeek
    �ڱ��򿪵��ļ��У�������һ������д������λ�á��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ�������в������ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
    ����<2>������Ϊ����ʼ�ƶ�λ�á�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�����ֵָ�����ļ��п�ʼ�ƶ���λ�á�����Ϊ���³���֮һ��
	1��#�ļ��ף� 2��#�ļ�β�� 3��#����λ�á������������ʡ�ԣ�Ĭ��ֵΪ��#�ļ��ס���
    ����<3>������Ϊ���ƶ����롱������Ϊ�������ͣ�int����������ֵָ���������ʼ�ƶ�λ�õ��ƶ����ȡ�
*/
LIBAPI(BOOL, krnln_FSeek)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return FALSE;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return FALSE;
	PMDATA_INF pArgInf = &ArgInf;
	BOOL bRet = FALSE;

	if(pFile->nType == 1 || pFile->nType == 3)//�����ļ� �����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwMoveMethod;
		switch(pArgInf[1].m_int)
		{
		case 2://#�ļ�β
			dwMoveMethod = FILE_END;
			break;
		case 3://#����λ��
			dwMoveMethod = FILE_CURRENT;
			break;
		default://#�ļ���
			dwMoveMethod = FILE_BEGIN;
		}
		bRet = SetFilePointer(hFile,pArgInf[2].m_int,NULL,dwMoveMethod);

	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;
		DWORD dwMoveMethod;
		switch(pArgInf[1].m_int)
		{
		case 2://#�ļ�β
			dwMoveMethod = CMyMemFile::SeekPosition::end;
			break;
		case 3://#����λ��
			dwMoveMethod = CMyMemFile::SeekPosition::current;
			break;
		default://#�ļ���
			dwMoveMethod = CMyMemFile::SeekPosition::begin;
		}
		
		bRet = (pMemFile->Seek(pArgInf[2].m_int,dwMoveMethod) != -1);

	}
	return bRet;

}
