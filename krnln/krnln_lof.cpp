#include "stdafx.h"
#include "MyMemFile.h"
//�ļ���д - ȡ�ļ�����
/*
    ���ø�ʽ�� �������͡� ȡ�ļ����� �������� �ļ��ţ� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�lof
    ����ָ�������ļ��ĳߴ磬�óߴ����ֽ�Ϊ��λ����������ļ�����Ч��ʧ�ܣ����� -1 ��������Ϊ�������
    ����<1>������Ϊ���ļ��š�������Ϊ�������ͣ�int����������ֵָ�����������ļ��ţ����ļ��ű����ɡ����ļ������������ء�
*/
LIBAPI(int, krnln_lof)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return -1;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return -1;
	INT nRet = -1;

	if(pFile->nType ==1 || pFile->nType == 3)//�����ļ� �����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwHi;
		nRet = ::GetFileSize(hFile,&dwHi);


	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;
		nRet = pMemFile->GetFileSize();
	}
	return nRet;
}
