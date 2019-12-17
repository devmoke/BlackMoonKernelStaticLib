#include "stdafx.h"

//�ļ���д - ��ס�ļ�
/*
    ���ø�ʽ�� ���߼��͡� ��ס�ļ� �������� ��������������ļ��ţ������� �������������λ�ã������� ������������ĳ��ȣ��������� ��������ʱ��ݣ� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�lock
    �������ɸ����̷���ͬһ���ļ��Ļ����У�ʹ�ñ�����ܾ������û��Ա����ļ��е�ĳ��������ж�д���ʡ��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
    ����<1>������Ϊ����������������ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
    ����<2>������Ϊ���������������λ�á�������Ϊ�������ͣ�int������λ��ֵ�� 0 ��ʼ��
    ����<3>������Ϊ��������������ĳ��ȡ�������Ϊ�������ͣ�int������
    ����<4>������Ϊ����������ʱ�䡱������Ϊ�������ͣ�int���������Ա�ʡ�ԡ�������ָ������ʧ�ܺ󷴸��������Եĺ������������ʡ�ԣ�Ĭ��Ϊ 0 ����һ��ʧ���������ء��������ֵ�ṩΪ -1 ���򷴸��������ԣ�ֱ�������ɹ�Ϊֹ��

*/
LIBAPI(BOOL, krnln_lock)
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
	OVERLAPPED Overlapped;
	memset(&Overlapped,0,sizeof(OVERLAPPED));
	Overlapped.Offset = pArgInf[1].m_int;
	DWORD dwFlags = LOCKFILE_FAIL_IMMEDIATELY;
	if(pArgInf[3].m_dtDataType != _SDT_NULL)
	{
		if(pArgInf[3].m_int== -1)
			dwFlags = 0;
		else if(pArgInf[3].m_int > 0)
		{	
			DWORD dwStart = ::GetTickCount();
			BOOL bRet;
			INT nVal;
			do
			{
				bRet = LockFileEx(hFile,LOCKFILE_FAIL_IMMEDIATELY,0,pArgInf[2].m_int,0,&Overlapped);
				nVal = GetTickCount() - dwStart;
			}while(bRet == FALSE && nVal <= pArgInf[3].m_int);

			return bRet;
		}

	}

	return LockFileEx(hFile,
		dwFlags,
		0,
		pArgInf[2].m_int,
		0,
		&Overlapped);

}
