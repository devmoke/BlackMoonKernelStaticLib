#include "stdafx.h"

//�ļ���д - �����ļ�
/*
    ���ø�ʽ�� ���߼��͡� �����ļ� �������� ��������������ļ��ţ������� �������������λ�ã������� ������������ĳ��ȣ� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�Unlock
    ����ɡ���ס�ļ���������ļ������е��������ɹ������棬ʧ�ܷ��ؼ١�ע�⣺���������ʱ���ṩ�Ĳ���ֵ��������á���ס�ļ�������ʱ���ṩ�Ĳ���ֵ��ȫһ�¡�������Ϊ�������
    ����<1>������Ϊ����������������ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
    ����<2>������Ϊ���������������λ�á�������Ϊ�������ͣ�int������λ��ֵ�� 0 ��ʼ��
    ����<3>������Ϊ��������������ĳ��ȡ�������Ϊ�������ͣ�int������
*/
LIBAPI(BOOL, krnln_Unlock)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return FALSE;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return FALSE;
	if(pFile->nType !=1)//�ڴ��ļ�
		return TRUE;
	HANDLE hFile = (HANDLE)pFile->FileHandle;
	PMDATA_INF pArgInf = &ArgInf;

	return UnlockFile(hFile,
		pArgInf[1].m_int,
		0,
		pArgInf[2].m_int,
		0);
}
