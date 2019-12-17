#include "stdafx.h"
#include "MyMemFile.h"
//�ļ���д - �Ƶ��ļ�β
/*
    ���ø�ʽ�� ���߼��͡� �Ƶ��ļ�β �������� �����в������ļ��ţ� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�SeekToEnd
    �ڱ��򿪵��ļ��У�������һ������д������λ�õ��ļ�β���ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ�������в������ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
*/
LIBAPI(BOOL, krnln_SeekToEnd)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return FALSE;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return FALSE;

	BOOL bRet = FALSE;

	if(pFile->nType ==1 || pFile->nType == 3)//�����ļ� �����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		bRet = SetFilePointer(hFile,0,NULL,FILE_END);

	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;
		bRet = (pMemFile->Seek(0,CMyMemFile::SeekPosition::end) != -1);

	}
	return bRet;
}
