#include "stdafx.h"

//���̲��� - д���ļ�
/*
    ���ø�ʽ�� ���߼��͡� д���ļ� ���ı��� �ļ������ֽڼ� ��д���ļ������ݣ�... �� - ϵͳ����֧�ֿ�->���̲���
    Ӣ�����ƣ�WriteFile
    ������������һ���������ֽڼ�˳��д��ָ���ļ��У��ļ�ԭ�����ݱ����ǡ��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ���������������������һ���������Ա��ظ���ӡ�
    ����<1>������Ϊ���ļ�����������Ϊ���ı��ͣ�text������
    ����<2>������Ϊ����д���ļ������ݡ�������Ϊ���ֽڼ���bin������
*/
LIBAPI(BOOL, krnln_WriteFile)
{
	PMDATA_INF pArgInf = &ArgInf;
	HANDLE hFile = CreateFile(ArgInf.m_pText,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_ARCHIVE,
		0);
	
	BOOL bRet = FALSE;
	if(hFile != INVALID_HANDLE_VALUE)
	{

		DWORD dwNumOfByteRead;
		bRet = TRUE;
		for(INT i=1;i < nArgCount;i++)
		{
			LPBYTE pData = pArgInf[i].m_pBin + 2*sizeof(INT);
			INT nLen = pArgInf[i].m_pInt[1];

			if(WriteFile(hFile,pData,nLen,&dwNumOfByteRead,NULL)==FALSE)
			{
				bRet = FALSE;
				break;
			}
/*			if(FlushFileBuffers(hFile)==FALSE)
			{
				bRet = FALSE;
				break;
			}*/
		}
		CloseHandle(hFile);
	}
	return bRet;
}
