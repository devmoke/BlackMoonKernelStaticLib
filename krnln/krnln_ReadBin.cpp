#include "stdafx.h"
#include "MyMemFile.h"
#include "Myfunctions.h"
//�ļ���д - �����ֽڼ�
/*
    ���ø�ʽ�� ���ֽڼ��� �����ֽڼ� �������� ���������ݵ��ļ��ţ������� ���������ݵĳ��ȣ� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�ReadBin
    �������������ļ��е�ǰ��дλ�ö�ȡ������һ���ֽڼ����ݣ�ʵ�ʶ��볤�ȣ������ص��ֽڼ��ĳߴ磩���ܻ�С�������볤�ȡ��������ʧ�ܣ�������һ�����ֽڼ������Զ�����ǰ�ļ���дλ���Ƶ��ļ�β����������Ϊ�������
    ����<1>������Ϊ�����������ݵ��ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
    ����<2>������Ϊ�����������ݵĳ��ȡ�������Ϊ�������ͣ�int������
*/
LIBAPI(void*, krnln_ReadBin)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return NULL;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return NULL;
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[1].m_int <=0)
		return NULL;

	LPBYTE pbRet = NULL;

	if(pFile->nType == 1)//�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		INT nLen = pArgInf[1].m_int;
		LPBYTE pData = new BYTE[nLen];
		INT nRet = ReadFile(hFile, pData, nLen, &dwNumOfByteRead, 0);
		if(nRet == FALSE)
		{
			delete[] pData;
			return NULL;
		}
		nLen = dwNumOfByteRead;
		pbRet = CloneBinData(pData,nLen);
		delete[] pData;
		

	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;
		INT nLen = pArgInf[1].m_int;
		LPBYTE pData =  (LPBYTE)E_MAlloc_Nzero(nLen+2*sizeof(INT));
		*(LPINT)pData = 1;
		*(LPINT)(pData + sizeof(INT)) = nLen;
		DWORD dwNumOfByteRead = pMemFile->Read (pData + 2*sizeof(INT),nLen);
		if(dwNumOfByteRead == 0)
		{
			E_MFree(pData);
			return NULL;
		}
		*(LPINT)(pData + sizeof(INT)) = dwNumOfByteRead;
		pbRet = pData;

	}else if (pFile->nType == 3) //�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		DWORD dwNumOfByteRead;
		INT nLen = pArgInf[1].m_int;
		LPBYTE pData = new BYTE[nLen];
		INT nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
		INT nRet = ReadFile(hFile, pData, nLen, &dwNumOfByteRead, 0);
		if(nRet == FALSE)
		{
			delete[] pData;
			return NULL;
		}
		nLen = dwNumOfByteRead;
		E_RC4_Calc(nPos, pData, nLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
		pbRet = CloneBinData(pData,nLen);
		delete[] pData;
	}
	return pbRet;
}
