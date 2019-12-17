#include "stdafx.h"
#include "MyMemFile.h"
#include "Myfunctions.h"
#include <vector>

using namespace std;
//�ļ���д - �����ı�
/*
    ���ø�ʽ�� ���ı��͡� �����ı� �������� �������ı����ݵ��ļ��ţ��������� �������ı����ݵĳ��ȣݣ� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�ReadText
    �������������ļ��е�ǰ��дλ�ö�ȡ������һ���ı����ݣ�ʵ�ʶ��볤�ȣ��������ı��ĳߴ磩���ܻ�С�������볤�ȡ�����������д����ֽ� 0 �� 26���ı�������־�����������ظ��ֽ�֮ǰ�����ݡ��������ʧ�ܣ�������һ�����ı������Զ�����ǰ�ļ���дλ���Ƶ��ļ�β����������Ϊ�������
    ����<1>������Ϊ���������ı����ݵ��ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
    ����<2>������Ϊ���������ı����ݵĳ��ȡ�������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������������ʡ�ԣ�Ĭ�϶����ļ��е������ı����ݡ�
*/
LIBAPI(char*, krnln_ReadText)
{
	PFILEELEMENT pFile = (PFILEELEMENT)ArgInf.m_pCompoundData;
	if(pFile==NULL)
		return NULL;
	if(IsInFileMangerList(pFile)==FALSE)//������Ϸ���
		return NULL;
	PMDATA_INF pArgInf = &ArgInf;
	if(pArgInf[1].m_dtDataType != _SDT_NULL && pArgInf[1].m_int <=0)
		return NULL;

	char* pszRet = NULL;

	if(pFile->nType ==1)//�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
		if(orgLoc == HFILE_ERROR)
		{
			SetFilePointer(hFile,0,NULL,FILE_END);
			return NULL;
		}

		DWORD dwNumOfByteRead;
		INT nLen;
		if(pArgInf[1].m_dtDataType == _SDT_NULL)
			nLen = GetFileSize(hFile,NULL) - orgLoc;
		else
			nLen = pArgInf[1].m_int;
		//��Ĵ���
		vector<MEMSP> vecMEMSP;
		INT nTLen = 0;
		for (INT i=0; i<nLen; i+=4096)
		{
			MEMSP tmpMEMSP;
			tmpMEMSP.pData = (char*)malloc(4096);
			INT nRet = ReadFile(hFile, tmpMEMSP.pData, min(nLen-i,4096), &dwNumOfByteRead, 0);
			if(nRet == FALSE)
			{
				SetFilePointer(hFile, 0, NULL, FILE_END);
				free(tmpMEMSP.pData);
				break;
			}
			BOOL bFind = FALSE;
			for (INT j=0; j < dwNumOfByteRead; j++)
			{
				if (tmpMEMSP.pData[j] == 0 || tmpMEMSP.pData[j] == 26)
				{
					dwNumOfByteRead = j;
					orgLoc++;// ��������ֽ�
					bFind = TRUE;
					break;
				}
			}
			tmpMEMSP.nLen = dwNumOfByteRead;
			nTLen += dwNumOfByteRead;
			vecMEMSP.push_back(tmpMEMSP);
			if (bFind || dwNumOfByteRead != 4096)
				break;
		}
		if (nTLen > 0)
		{
			pszRet = (LPSTR)E_MAlloc_Nzero(nTLen + 1);
			orgLoc += nTLen;
			SetFilePointer(hFile, orgLoc, NULL, FILE_BEGIN);
			
			LPSTR pszRetold = pszRet;
			vector<MEMSP>::iterator iterMEMSP;
			for (iterMEMSP = vecMEMSP.begin(); iterMEMSP != vecMEMSP.end(); iterMEMSP++)
			{
				memcpy(pszRetold, iterMEMSP->pData, iterMEMSP->nLen);
				pszRetold += iterMEMSP->nLen;
				free(iterMEMSP->pData);
			}
			pszRet[nTLen] = 0;
		}
		vecMEMSP.clear();
		return pszRet;
		// ����ԭ���Ĵ���
// 		char* pData = new char[nLen];
// 		INT nRet = ReadFile(hFile, pData, nLen, &dwNumOfByteRead, 0);
// 		if(nRet == FALSE)
// 		{
// 			SetFilePointer(hFile,0,NULL,FILE_END);
// 			delete[] pData;
// 			return NULL;
// 		}
// 		nLen = 0;
// 		LPSTR pStr = pData;
// 		while(nLen < (INT)dwNumOfByteRead)
// 		{
// 			if(*pStr ==0 || *pStr ==26)
// 				break;
// 			nLen++;
// 			pStr++;
// 		}
// 		pszRet = (LPSTR)E_MAlloc_Nzero(nLen+1);
// 		orgLoc += nLen;
// 		SetFilePointer(hFile,orgLoc,NULL,FILE_BEGIN);
// 		strncpy(pszRet,pData,nLen);
// 		pszRet[nLen] = 0;
// 		
// 		delete[] pData;		

	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;

		INT orgLoc = pMemFile->GetPosition();

		DWORD dwNumOfByteRead;
		INT nLen;
		LPSTR pBufStart, pBufMax;
		if(pArgInf[1].m_dtDataType == _SDT_NULL)
			nLen = -1;
		else
			nLen = pArgInf[1].m_int;

		dwNumOfByteRead = pMemFile->GetBufferPtr (CMyMemFile::BufferCommand::bufferRead,nLen,(void **)&pBufStart,(void **)&pBufMax);

		LPSTR pStr = pBufStart;
		nLen = 0;
		while(nLen < (INT)dwNumOfByteRead)
		{
			if(*pStr ==0 || *pStr ==26)
				break;
			nLen++;
			pStr++;
		}
		pszRet = (LPSTR)E_MAlloc_Nzero(nLen+1);
		orgLoc += nLen;
		pMemFile->Seek(orgLoc,CMyMemFile::SeekPosition::begin);
		strncpy(pszRet,pBufStart,nLen);
		pszRet[nLen] = 0;
	}if(pFile->nType ==3)//�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
		if(orgLoc == HFILE_ERROR)
		{
			SetFilePointer(hFile,0,NULL,FILE_END);
			return NULL;
		}
		
		DWORD dwNumOfByteRead;
		INT nLen;
		if(pArgInf[1].m_dtDataType == _SDT_NULL)
			nLen = GetFileSize(hFile,NULL) - orgLoc;
		else
			nLen = pArgInf[1].m_int;
		//��Ĵ���
		vector<MEMSP> vecMEMSP;
		INT nTLen = 0;
		for (INT i=0; i<nLen; i+=4096)
		{
			MEMSP tmpMEMSP;
			tmpMEMSP.pData = (char*)malloc(4096);
			INT nPos = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
			INT nRet = ReadFile(hFile, tmpMEMSP.pData, min(nLen-i,4096), &dwNumOfByteRead, 0);
			if(nRet == FALSE)
			{
				SetFilePointer(hFile, 0, NULL, FILE_END);
				free(tmpMEMSP.pData);
				break;
			}
			BOOL bFind = FALSE;
			E_RC4_Calc(nPos, (unsigned char*)tmpMEMSP.pData, dwNumOfByteRead, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
			for (INT j=0; j < dwNumOfByteRead; j++)
			{
				if (tmpMEMSP.pData[j] == 0 || tmpMEMSP.pData[j] == 26)
				{
					dwNumOfByteRead = j;
					orgLoc++;// ��������ֽ�
					bFind = TRUE;
					break;
				}
			}
			tmpMEMSP.nLen = dwNumOfByteRead;
			nTLen += dwNumOfByteRead;
			vecMEMSP.push_back(tmpMEMSP);
			if (bFind || dwNumOfByteRead != 4096)
				break;
		}
		if (nTLen > 0)
		{
			pszRet = (LPSTR)E_MAlloc_Nzero(nTLen + 1);
			orgLoc += nTLen;
			SetFilePointer(hFile, orgLoc, NULL, FILE_BEGIN);
			
			LPSTR pszRetold = pszRet;
			vector<MEMSP>::iterator iterMEMSP;
			for (iterMEMSP = vecMEMSP.begin(); iterMEMSP != vecMEMSP.end(); iterMEMSP++)
			{
				memcpy(pszRetold, iterMEMSP->pData, iterMEMSP->nLen);
				pszRetold += iterMEMSP->nLen;
				free(iterMEMSP->pData);
			}
			pszRet[nTLen] = 0;
		}
		vecMEMSP.clear();
		return pszRet;	
	}
	return pszRet;
}
