#include "stdafx.h"
#include "MyMemFile.h"
#include "Myfunctions.h"

//�ļ���д - �����ı���
/*
    ���ø�ʽ�� ���߼��͡� �����ı��� �������� ��д���ı����ļ��ţ�ͨ���� ��д�����ı���... �� - ϵͳ����֧�ֿ�->�ļ���д
    Ӣ�����ƣ�InsLine
    ��������������һ�λ������ı��е��ļ��е�ǰ��дλ�ô������ļ�����ʱ�������"#��д"��"#�Ķ�"Ȩ�ޡ��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ���������������������һ���������Ա��ظ���ӡ�
    ����<1>������Ϊ����д���ı����ļ��š�������Ϊ�������ͣ�int���������ļ����ɡ����ļ������������ء�
    ����<2>������Ϊ����д�����ı���������Ϊ��ͨ���ͣ�all����������ֵ�����Ϊ�ı��������ݣ����Զ�����ת��������޷�ת��������������Ϊ�ֽڼ����ӳ���ָ�롢����û��Զ����������ͣ�����д�������ݡ�
*/
LIBAPI(BOOL, krnln_InsLine)
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
		INT orgLoc = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
		if(orgLoc == HFILE_ERROR)
			return FALSE;

		DWORD dwNumOfByteRead;
		INT nBkLen = GetFileSize(hFile,NULL) - orgLoc;
		LPBYTE pBkData = NULL;
		if(nBkLen >0)
		{
			pBkData = new BYTE[nBkLen];
			if(!ReadFile(hFile, pBkData, nBkLen, &dwNumOfByteRead, 0))
			{
				delete[] pBkData;
				return FALSE;
			}
			SetFilePointer(hFile,orgLoc,NULL,FILE_BEGIN);//�ָ�ԭλ��
		}

		bRet = TRUE;
		for(INT i=1;i < nArgCount;i++)
		{
			LPSTR pData;
			BOOL bNeedFree = FALSE;
			if(pArgInf[i].m_dtDataType == SDT_TEXT)
				pData = pArgInf[i].m_pText;
			else
			{
				pData = SDataToStr(&pArgInf[i]);
				if(pData == NULL)
				{
					WriteFile(hFile,"\r\n",2,&dwNumOfByteRead,NULL);
//					FlushFileBuffers(hFile);
					continue;
				}
				bNeedFree = TRUE;
			}

			INT nLen = mystrlen(pData);
			if(nLen>0)
			{
				if(WriteFile(hFile,pData,nLen,&dwNumOfByteRead,NULL))
				{
					WriteFile(hFile,"\r\n",2,&dwNumOfByteRead,NULL);
//					if(FlushFileBuffers(hFile)==FALSE)
//						bRet = FALSE;
				}
				else
					bRet = FALSE;
			}

			if(bNeedFree)
				free(pData);

			if(bRet == FALSE)
				break;

		}
		if(bRet && pBkData)//���Ϻ��
		{
			orgLoc = SetFilePointer(hFile,0,NULL,FILE_CURRENT);//���µ�ǰλ��,�Ա�ָ�
			if(WriteFile(hFile,pBkData, nBkLen,&dwNumOfByteRead,NULL))
			{
				SetFilePointer(hFile,orgLoc,NULL,FILE_BEGIN);//�ָ�ԭλ��
//				if(FlushFileBuffers(hFile)==FALSE)
//					bRet = FALSE;
			}
			else
				bRet = FALSE;
			
		}
		if(pBkData)
			delete[] pBkData;

	}else if(pFile->nType ==2)//�ڴ��ļ�
	{
		CMyMemFile* pMemFile = (CMyMemFile*) pFile->FileHandle;

		INT orgLoc = pMemFile->GetPosition();

		LPBYTE pBufStart, pBufMax;

		INT nBkLen = pMemFile->GetBufferPtr (CMyMemFile::BufferCommand::bufferRead,-1,(void **)&pBufStart,(void **)&pBufMax);
		LPBYTE pBkData = NULL;
		if(nBkLen >0)
		{
			pBkData = new BYTE[nBkLen];
			memcpy(pBkData,pBufStart,nBkLen);
		}

		bRet = TRUE;
		for(INT i=1;i < nArgCount;i++)
		{
			LPSTR pData;
			BOOL bNeedFree = FALSE;
			if(pArgInf[i].m_dtDataType == SDT_TEXT)
				pData = pArgInf[i].m_pText;
			else
			{
				pData = SDataToStr(&pArgInf[i]);
				if(pData == NULL)
					continue;
				bNeedFree = TRUE;
			}

			INT nLen = mystrlen(pData);
			if(nLen>0)
				pMemFile->Write(pData,nLen);
			pMemFile->Write("\r\n",2);

			if(bNeedFree)
				free(pData);
		}
		if(pBkData)
		{
			orgLoc = pMemFile->GetPosition();
			pMemFile->Write(pBkData, nBkLen);
			delete[] pBkData;
			pMemFile->Seek (orgLoc,CMyMemFile::SeekPosition::begin);
		}

	}else if(pFile->nType ==3)//�����ļ�
	{
		HANDLE hFile = (HANDLE)pFile->FileHandle;
		INT orgLoc = SetFilePointer(hFile,0,NULL,FILE_CURRENT);
		if(orgLoc == HFILE_ERROR)
			return FALSE;
		
		DWORD dwNumOfByteRead;
		INT nPos;
		INT nBkLen = GetFileSize(hFile,NULL) - orgLoc;
		LPBYTE pBkData = NULL;
		if(nBkLen >0)
		{
			pBkData = new BYTE[nBkLen];
			if(!ReadFile(hFile, pBkData, nBkLen, &dwNumOfByteRead, 0))
			{
				delete[] pBkData;
				return FALSE;
			}
			nBkLen = dwNumOfByteRead;
			E_RC4_Calc(orgLoc, (unsigned char*)pBkData, nBkLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
			SetFilePointer(hFile,orgLoc,NULL,FILE_BEGIN);//�ָ�ԭλ��
		}

		unsigned char pszRN[2] = {0};
		bRet = TRUE;
		for(INT i=1;i < nArgCount;i++)
		{
			LPSTR pData;
			BOOL bNeedFree = FALSE;
			if(pArgInf[i].m_dtDataType == SDT_TEXT)
				pData = pArgInf[i].m_pText;
			else
			{
				pData = SDataToStr(&pArgInf[i]);
				if(pData == NULL)
				{
					nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
					pszRN[0] = '\r';
					pszRN[1] = '\n';
					E_RC4_Calc(nPos, pszRN, 2, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
					WriteFile(hFile, pszRN, 2, &dwNumOfByteRead,NULL);
					continue;
				}
				bNeedFree = TRUE;
			}
			
			INT nLen = mystrlen(pData);
			if(nLen>0)
			{
				if (!bNeedFree)
				{
					LPSTR pTMP = (LPSTR)malloc(nLen);
					memcpy(pTMP, pData, nLen);
					pData = pTMP;
					bNeedFree = TRUE;
				}
				nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
				E_RC4_Calc(nPos, (unsigned char*)pData, nLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
				if(WriteFile(hFile,pData,nLen,&dwNumOfByteRead,NULL))
				{
					nPos = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
					pszRN[0] = '\r';
					pszRN[1] = '\n';
					E_RC4_Calc(nPos, pszRN, 2, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
					WriteFile(hFile, pszRN, 2, &dwNumOfByteRead,NULL);
				}
				else
					bRet = FALSE;
			}
			
			if(bNeedFree)
				free(pData);
			
			if(bRet == FALSE)
				break;
		}

		if(bRet && pBkData)//���Ϻ��
		{
			orgLoc = SetFilePointer(hFile,0,NULL,FILE_CURRENT);//���µ�ǰλ��,�Ա�ָ�
			E_RC4_Calc(orgLoc, (unsigned char*)pBkData, nBkLen, pFile->strTable, pFile->nCryptStart, pFile->strMD5);
			if(WriteFile(hFile,pBkData, nBkLen,&dwNumOfByteRead,NULL))
				SetFilePointer(hFile,orgLoc,NULL,FILE_BEGIN);//�ָ�ԭλ��
			else
				bRet = FALSE;
		}
		if(pBkData)
			delete[] pBkData;
	}
	return bRet;
}
