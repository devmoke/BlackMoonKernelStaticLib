#include "stdafx.h"
#include "MyMemFile.h"
//�ļ���д - ȡ��дλ��
/*
    ���ø�ʽ�� �������͡� ȡ��дλ�� �������� �ļ��ţ� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�loc
    ����ָ�������ļ��ĵ�ǰ��/дλ�ã�λ��ֵ�� 0 ��ʼ����������ļ�����Ч��ʧ�ܣ����� -1 ��������Ϊ�������
    ����<1>������Ϊ���ļ��š�������Ϊ�������ͣ�int����������ֵָ�����������ļ��ţ����ļ��ű����ɡ����ļ������������ء�
*/
LIBAPI(int, krnln_loc)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return -1;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return -1;
	INT nRet = HFILE_ERROR;

	if(pFile->nType == 1 || pFile->nType == 3)//�����ļ� �����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		nRet = SetFilePointer(hFile,0,NULL,FILE_CURRENT);

	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;
		nRet = pMemFile->GetPosition();
	}
	return nRet;
}
