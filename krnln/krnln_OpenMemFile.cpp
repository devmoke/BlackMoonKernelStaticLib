#include "stdafx.h"
#include "MyMemFile.h"
//�ļ���д - ���ڴ��ļ�
/*
    ���ø�ʽ�� �������͡� ���ڴ��ļ� ���� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�OpenMemFile
    ����һ���ڴ��ļ����Լ�����ڴ�Ϊ�洢���ʶ����ݽ����ļ�ʽ�Ŀ��������������ɹ����ر����ļ����ļ��ţ�ʧ�ܷ��� 0��������Ϊ�������
*/
LIBAPI(void*, krnln_OpenMemFile)
{
	CMyMemFile* pMemFile = new CMyMemFile();
	if(pMemFile)
	{
		PFILEELEMENT pFile = new FILEELEMENT;
		pFile->nType = 2;
		pFile->FileHandle = pMemFile;
		AddFileMangerList(pFile);
		return pFile;
	}
	return NULL;
}
