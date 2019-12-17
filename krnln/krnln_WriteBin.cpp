#include "stdafx.h"
#include "MyMemFile.h"
#include "Myfunctions.h"
//�ļ���д - д���ֽڼ�
/*
    ���ø�ʽ�� ���߼��͡� д���ֽڼ� �������� ��д�����ݵ��ļ��ţ��ֽڼ� ��д�����ֽڼ����ݣ�... �� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�WriteBin
    ����������д��һ�λ������ֽڼ����ݵ��ļ��е�ǰ��дλ�ô����ɹ������棬ʧ�ܷ��ؼ١�������Ϊ���������������������һ���������Ա��ظ���ӡ�
    ����<1>������Ϊ����д�����ݵ��ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
    ����<2>������Ϊ����д�����ֽڼ����ݡ�������Ϊ���ֽڼ���bin������
*/
LIBAPI(BOOL, krnln_WriteBin)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return NULL;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return NULL;
	PMDATA_INF pArgInf = &ArgInf;

	BOOL bRet = FALSE;

	if(pFile->nType ==1)//�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
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
		

	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;
		bRet = TRUE;
		for(INT i=1;i < nArgCount;i++)
		{
			LPBYTE pData = pArgInf[i].m_pBin + 2*sizeof(INT);
			INT nLen = pArgInf[i].m_pInt[1];
			pMemFile->Write(pData,nLen);
		}

	}else if (pFile->nType == 3) //�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		LPBYTE pData;
		INT nMaxLen = 0;
		INT nLen, i, nPos;
		bRet = TRUE;
		for(i=1;i < nArgCount;i++)
		{
			nLen = pArgInf[i].m_pInt[1];
			if (nLen > 0)
				nMaxLen = max(nMaxLen, nLen);
		}
		if (nMaxLen > 0)
			pData = new unsigned char[nMaxLen];
		for(i=1;i < nArgCount;i++)
		{
			nLen = pArgInf[i].m_pInt[1];
			if (nLen > 0)
			{
				memcpy(pData, pArgInf[i].m_pBin + 2*sizeof(INT), nLen);

				nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
				E_RC4_Calc(nPos, pData, nLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
				if(WriteFile(hFile,pData,nLen,&dwNumOfByteRead,NULL)==FALSE)
				{
					delete []pData;
					bRet = FALSE;
					break;
				}
			}
		}
		delete []pData;
	}
	return bRet;
}
